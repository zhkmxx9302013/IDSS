# -*- coding: utf-8 -*-
import os
import file_pb2
import clips_facts_pb2
from clips_service import ClipsService
from base_controller import BaseController

from common_utils import RULE_FILE_PREFIX, FACT_FILE_PREFIX
import sys
reload(sys)
sys.setdefaultencoding('utf8')

class RuleController(BaseController):
    def __init__(self, failure_controller):
        """
        构造器，与故障控制器有聚合关系
        :param failure_controller: 故障控制器实例
        """
        self.clips_obj = ClipsService()
        self.template_list = [] # Template file list, that selected
        self.factFile_list = [] # Fact file list, that selected
        self.fc = failure_controller
        # self.fileptr = 0        # fact file ptr, the row index of the generated pandas dataframe
        # self.filerear = 0       # fact file rear ptr, the max row index of the generated pandas dataframe
        pass

    def initRuleController(self):
        self.clips_obj = ClipsService()

    def reset(self):
        """
        reset
        :return:
        """
        self.clips_obj.reset()

    def get_rulefile_list(self):
        """
        Get rule file list, return all the files suffixed with '.clp'
        :return:
        """
        rule_file_info_list = []

        # RULE_FILE_PREFIX is the rule files directory.
        for filename in os.listdir(RULE_FILE_PREFIX):
            if os.path.splitext(filename)[1] == '.clp':
                desc = str(self.get_filedesc(RULE_FILE_PREFIX, filename).encode('utf8'))
                ct = str(self.time_stamp2time(os.path.getctime(RULE_FILE_PREFIX + filename)).encode('utf8'))
                obj = file_pb2.rule_file_info(file_name=filename,
                                        file_desc=desc,
                                        create_time=ct)
                rule_file_info_list.append(obj)
        return rule_file_info_list

    def load_rulefiles(self, filelist):
        """
        加载规则文件
        :param filelist:
        :return:
        """
        self.clips_obj.load_rule_files(filelist)

    def get_slots(self):
        """
        获取CLIPS Slot names
        :return:
        """
        fact_list = []
        slot_dict = self.clips_obj.get_slots()
        for key, value in slot_dict.items():
            for item in value:
                obj = file_pb2.fact_list(template_name=str(key), slot_name=str(item))
                fact_list.append(obj)
        return fact_list

    def set_templates(self, templates):
        """
        设置选择的模板名称
        :param templates:
        :return:
        """
        self.template_list = templates

    def get_factfile_list(self):
        """
        获取 fact files
        :return:
        """
        fact_file_info_list = []
        for filename in os.listdir(FACT_FILE_PREFIX):
            if os.path.splitext(filename)[1] == '.csv':
                desc = str(self.get_filedesc(FACT_FILE_PREFIX, filename).encode('utf8'))
                ct = str(self.time_stamp2time(os.path.getctime(FACT_FILE_PREFIX + filename)).encode('utf8'))
                obj = file_pb2.fact_file_info(file_name=filename,
                                              file_desc=desc,
                                              create_time=ct)
                fact_file_info_list.append(obj)

        return fact_file_info_list

    def get_selected_slots(self):
        """
        获取所选的 slots
        :return:
        """
        fact_list = []
        slot_dict = self.clips_obj.get_slots()
        for key, value in slot_dict.items():
            for item in value:
                if str(key) in self.template_list:
                    obj = file_pb2.fact_list(template_name=str(key), slot_name=str(item))
                    fact_list.append(obj)
        return fact_list

    def load_factfiles(self, filelist):
        """
        Store the fact file list selected from the client
        :param filelist:
        :return:
        """
        self.factFile_list = filelist
        self.clips_obj.load_fact_file(filelist)

    def get_variables(self):
        """
        Get the optional variables from the facts file
        :return:
        """
        fact_var_obj = []
        for filename in self.factFile_list:
            with open(FACT_FILE_PREFIX + filename) as file:
                varname_list = file.readline().decode('gb2312').encode('utf8').split(',')
                varnval_list = file.readline().decode('gb2312').encode('utf8').split(',')
                for i in range(len(varname_list)):
                    obj = file_pb2.fact_var(file=filename, var_name=str(varname_list[i]), var_val=str(varnval_list[i]))
                    fact_var_obj.append(obj)
        return fact_var_obj

    def set_mapping_list(self, mapper):
        """Set template slot mapper"""
        self.clips_obj.set_mapping_list(mapper)

    def get_reasoning_result(self):
        """
        Get the reasoning result strings from the clips service
        :return:
        """
        self.clips_obj.update_data()
        self.clips_obj.generate_facts(self.clips_obj.generate_fact_str())
        data = self.clips_obj.get_fact_content()

        result_str, dlg_str = self.clips_obj.get_result()  # Reasoning result strings.

        # 设置故障信息
        self.fc.generate_failure(result_str, dlg_str)
        mark = self.clips_obj.get_EOF_mark() # Reading to the EOF marker.

        fact_data = clips_facts_pb2.fact_data(data=data)
        return clips_facts_pb2.result(res=result_str, wdlgres=dlg_str, end=mark, data=fact_data)

    def on_sim_start(self):
        """
        Initialize fileptr when reasoning process start
        :return:
        """
        # self.fileptr = 0
        # self.filerear = self.clips_obj.get_dataframe_size()

        self.clips_obj.set_record_name()





