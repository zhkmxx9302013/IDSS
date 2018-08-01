# -*- coding: utf-8 -*-
import os
import time
import clips_service
import file_pb2
import clips_facts_pb2
import json
from common_utils import RULE_FILE_PREFIX, FACT_FILE_PREFIX

class rule_controller():
    def __init__(self):
        self.clips_obj = clips_service.clips_service()
        self.template_list = [] # Template file list, that selected
        self.factFile_list = [] # Fact file list, that selected
        self.fileptr = 0        # fact file ptr, the row index of the generated pandas dataframe
        self.filerear = 0       # fact file rear ptr, the max row index of the generated pandas dataframe
        pass

    def get_rulefile_list(self):
        """Get rule file list"""
        rule_file_info_list = []
        for filename in os.listdir(RULE_FILE_PREFIX):
            if os.path.splitext(filename)[1] == '.clp':
                desc = str(self.__get_filedesc(RULE_FILE_PREFIX, filename).encode('utf8'))
                ct = str(self.__time_stamp2time(os.path.getctime(RULE_FILE_PREFIX + filename)).encode('utf8'))
                obj = file_pb2.rule_file_info(file_name=filename,
                                        file_desc=desc,
                                        create_time=ct)
                rule_file_info_list.append(obj)
        return rule_file_info_list

    def load_rulefiles(self, filelist):
        """Load rule files"""
        self.clips_obj.load_rule_files(filelist)

    def get_slots(self):
        """Get Slot names"""
        fact_list = []
        slot_dict = self.clips_obj.get_slots()
        for key, value in slot_dict.items():
            for item in value:
                obj = file_pb2.fact_list(template_name=str(key), slot_name=str(item))
                fact_list.append(obj)
        return fact_list

    def set_templates(self, templates):
        """Set the selected templates"""
        self.template_list = templates

    def get_factfile_list(self):
        """Get fact files"""
        fact_file_info_list = []
        for filename in os.listdir(FACT_FILE_PREFIX):
            if os.path.splitext(filename)[1] == '.csv':
                desc = str(self.__get_filedesc(FACT_FILE_PREFIX, filename).encode('utf8'))
                ct = str(self.__time_stamp2time(os.path.getctime(FACT_FILE_PREFIX + filename)).encode('utf8'))
                obj = file_pb2.fact_file_info(file_name=filename,
                                              file_desc=desc,
                                              create_time=ct)
                fact_file_info_list.append(obj)

        return fact_file_info_list

    def get_selected_slots(self):
        """Get the selected slots"""
        fact_list = []
        slot_dict = self.clips_obj.get_slots()
        for key, value in slot_dict.items():
            for item in value:
                if str(key) in self.template_list:
                    obj = file_pb2.fact_list(template_name=str(key), slot_name=str(item))
                    fact_list.append(obj)
        return fact_list

    def load_factfiles(self, filelist):
        """Store the fact file list selected from the client"""
        self.factFile_list = filelist
        self.clips_obj.load_fact_file(filelist)

    def get_variables(self):
        """Get the optional variables from the facts file"""
        fact_var_obj = []
        for filename in self.factFile_list:
            with open(FACT_FILE_PREFIX + filename) as file:
                varname_list = file.readline().split(',')
                varnval_list = file.readline().decode('gb2312').encode('utf8').split(',')
                for i in range(len(varname_list)):
                    obj = file_pb2.fact_var(file=filename, var_name=str(varname_list[i]), var_val=str(varnval_list[i]))
                    fact_var_obj.append(obj)
        return fact_var_obj

    def set_mapping_list(self, mapper):
        self.clips_obj.set_mapping_list(mapper)

    def get_reasoning_result(self):
        """Get the reasoning result strings from the clips service"""
        self.clips_obj.generate_facts(self.clips_obj.generate_fact_str(self.fileptr))
        data = self.clips_obj.get_fact_content(self.fileptr)

        self.fileptr = self.fileptr + 1
        result_str = self.clips_obj.get_result()
        mark = (self.fileptr == self.filerear)

        fact_data = clips_facts_pb2.fact_data(data=data)
        return clips_facts_pb2.result(res=result_str, end=mark, data=fact_data)

    def on_sim_start(self):
        """Initialize fileptr when reasoning process start"""
        self.fileptr = 0
        self.filerear = self.clips_obj.get_dataframe_size()
        self.clips_obj.set_record_name()


    def __time_stamp2time(self, timestamp):
        ts = time.localtime(timestamp)
        return time.strftime('%Y-%m-%d %H:%M:%S', ts)

    def __get_filedesc(self, prefix, filename):
        with open(prefix + 'desc.json', 'r') as file:
            json_obj = json.load(file)
            if json_obj.has_key(filename):
                file_desc = json_obj[filename]
            else:
                file_desc = ''
            file.close()
            return file_desc


