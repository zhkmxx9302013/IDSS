# encoding: utf-8
import clips
import file_pb2
import datetime
import pandas as pd
import numpy as np
from file_model import FileModel
from common_utils import RULE_FILE_PREFIX, TEMP_FILE_PREFIX, FACT_FILE_PREFIX
import sys
reload(sys)
sys.setdefaultencoding('utf8')

class ClipsService():
    def __init__(self):
        ##CONST CODE AREA
        self.CLIPS_FILE_LOAD_FAILED_CODE = 404
        self.CLIPS_FILE_LOAD_SUCCESS_CODE = 200
        self.codetype = sys.getfilesystemencoding()
        ##GLOBAL_AREA
        self.file_pointers = 1  # sim.data file read position
        self.m_nCount = 0
        self.data_file_name = TEMP_FILE_PREFIX + 'test_flight_facts.dat'
        self.clips_dribble_filename = TEMP_FILE_PREFIX + 'record.dat'
        self.clips_env = clips.Environment()
        self.engine = clips
        self.filemodel = FileModel()
        self.fact_filename = ''
        ## fact dataframe
        self.data = np.array([])
        self.data_header = np.array([])
        # self.dataframe = pd.DataFrame
        ## mapper
        self.mapper_list = []  # Template and slot mapping pair list
        self.record_name = ''  # Reasoning result record file name

    def reset(self):
        """
        reset
        :return:
        """
        self.file_pointers = 1  # sim.data file read position
        self.m_nCount = 0
        self.clips_env = clips.Environment()
        self.engine = clips
        self.filemodel.reset()
        self.filemodel.load_data(self.fact_filename)
        self.data = np.array([])
        self.data_header = np.array([])


    def update_data(self):
        """@public: Get fact data."""
        self.filemodel.update_data()
        self.data_header = self.filemodel.get_dataframe_header()
        self.data = self.filemodel.get_data()

    def get_EOF_mark(self):
        """
        返回仿真结束标志(EOF Mark).
        :return:
        """
        return self.filemodel.is_EOF()

    def load_rule_files(self, filenames):
        """@public: Load rule files"""
        self.__on_init_clips()
        try:
            for filename in filenames:
                self.engine.Load(RULE_FILE_PREFIX + filename)
            self.engine.DebugConfig.DribbleOn(self.clips_dribble_filename)
            self.engine.Reset()
            return self.CLIPS_FILE_LOAD_SUCCESS_CODE
        except self.engine.ClipsError as e:
            print(self.engine.ErrorStream.Read())
            return self.CLIPS_FILE_LOAD_FAILED_CODE

    def get_slots(self):
        """@public: Get Slot names orgnized by template names."""
        slot_dict = {}
        for template_name in self.engine.TemplateList():
            template = self.engine.FindTemplate(template_name)
            if len(template.Slots.Names()) > 0:
                slot_dict[template] = template.Slots.Names()
        return slot_dict

    def set_mapping_list(self, mapper):
        for item in mapper:
            # print(item.slot)
            self.mapper_list.append(item)
            # template = item.template
            # slot = item.slot
            # variable = item.variable

    def __on_init_clips(self):
        """@private: Initialize the CLIPS environment."""
        self.engine.Reset()
        self.engine.Clear()

    def load_fact_file(self, filename):
        """@public: Load fact file into dataframe"""
        if len(filename) <= 0:
            return
        self.fact_filename = filename
        self.filemodel.load_data(filename)

    def generate_fact_str(self):
        """@public: Generate assert fact formatted string"""
        tmp_template_name = ""
        assert_str = ""

        for mapper in self.mapper_list:
            template_name = mapper.template
            __idx = np.where(self.data_header == mapper.variable.decode('utf-8'))[0][0]

            slot_str = " (" + mapper.slot + " " + str(self.data[__idx]) + ')'
            if not tmp_template_name == template_name:
                if len(assert_str) > 0:
                    assert_str = assert_str + ')\n'
                    pt_str = "(" + template_name + slot_str
                    assert_str = assert_str + pt_str
                else:
                    pt_str = "(" + template_name + slot_str
                    assert_str = assert_str + pt_str

                tmp_template_name = template_name
            else:
                assert_str = assert_str + slot_str
        return (assert_str + ')')#.decode('gb2312').encode('utf8')

    def get_fact_content(self):
        """@public: Get the row of the dataframe (specific row of the facts file)"""
        # self.get_data()
        strs = ""
        for item in self.data:
            strs = strs + str(item) + ";"

        return strs #.decode('gb2312').encode('utf-8')

    def generate_facts(self, factstr):
        """@public: Generate fact file"""
        with open(self.data_file_name, 'w+') as f:
            f.writelines(factstr)

    def set_record_name(self):
        """@public: Generate record file"""
        nowTime = datetime.datetime.now().strftime('%Y%m%d-%H%M%S')
        self.record_name = TEMP_FILE_PREFIX + 'record/ '+ nowTime + '.record'
        file = open(self.record_name, 'w')
        file.close()

    # def __get_dataframe_size(self):
    #     """@decrepte: Get the whole fact files' row size"""
    #     return len(self.dataframe)



    def get_result(self):
        """@public: """
        self.engine.Reset()
        self.engine.LoadFacts(self.data_file_name)
        self.engine.Run()
        std_str = self.engine.StdoutStream.Read()
        dlg_str = self.engine.DialogStream.Read()
        # disp_str = CLIPS_HPROSE.DisplayStream.Read()
        if not dlg_str is None:
            pass
        else:
            dlg_str = 'NaN'

        if not std_str is None:
            pass
        else:
            std_str = 'NaN'

        fileobj = open(self.record_name, 'a')
        fileobj.writelines(std_str + '\n' + dlg_str + '\n')
        print std_str, dlg_str
        return std_str, dlg_str
