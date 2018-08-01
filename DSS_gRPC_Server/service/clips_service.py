# encoding: utf-8
import clips
import file_pb2
import datetime
import pandas as pd
from common_utils import RULE_FILE_PREFIX, TEMP_FILE_PREFIX, FACT_FILE_PREFIX


class clips_service():
    def __init__(self):
        ##CONST CODE AREA
        self.CLIPS_FILE_LOAD_FAILED_CODE = 404
        self.CLIPS_FILE_LOAD_SUCCESS_CODE = 200

        ##GLOBAL_AREA
        self.file_pointers = 1  # sim.data file read position
        self.m_nCount = 0
        self.data_file_name = TEMP_FILE_PREFIX + 'test_flight_facts.dat'
        self.clips_dribble_filename = TEMP_FILE_PREFIX + 'record.dat'
        self.clips_env = clips.Environment()
        self.engine = clips
        ## fact dataframe
        self.dataframe = pd.DataFrame
        ## mapper
        self.mapper_list = []
        self.record_name = '' #Reasoning result record file name

    def load_rule_files(self, filenames):
        """@public: Load rule files"""
        self.__on_init_clips()
        try:
            for filename in filenames:
                self.engine.Load(RULE_FILE_PREFIX + filename)

            self.engine.DebugConfig.DribbleOn(self.clips_dribble_filename)
            self.engine.Reset()
            return self.CLIPS_FILE_LOAD_SUCCESS_CODE
        except self.engine.ClipsError, e:
            print self.engine.ErrorStream.Read()
            return self.CLIPS_FILE_LOAD_FAILED_CODE

    def get_slots(self):
        """@public: Get Slot names orgnized by template name."""
        slot_dict = {}
        for template_name in self.engine.TemplateList():
            template = self.engine.FindTemplate(template_name)

            if len(template.Slots.Names()) > 0:
                slot_dict[template] = template.Slots.Names()

        return slot_dict

    def set_mapping_list(self, mapper):
        for item in mapper:
            print(item.slot)
            self.mapper_list.append(item)
            # template = item.template
            # slot = item.slot
            # variable = item.variable

    def __on_init_clips(self):
        """@private: Initialize the CLIPS environment."""
        self.engine.Reset()
        self.engine.Clear()

    def load_fact_file(self, filename):
        """Load fact file into dataframe"""
        if len(filename) <= 0:
            return

        i = 0
        for file in filename:
            df = pd.read_csv(FACT_FILE_PREFIX + file)
            if i == 0:
                self.dataframe = df
                i = i + 1
            else:
                pd.concat([self.dataframe, df], axis=1, join='inner')

    def generate_fact_str(self, fileptr):
        """Generate assert fact formatted string"""
        tmp_template_name = ""
        assert_str = ""
        for mapper in self.mapper_list:
            template_name = mapper.template
            slot_str = " (" + mapper.slot + " " + str(self.dataframe[mapper.variable][fileptr]) + ')'
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

        return (assert_str + ')').decode('gb2312').encode('utf8')

    def get_fact_content(self, fileptr):
        """Get the row of the dataframe"""
        strs = ""
        for item in self.dataframe.iloc[fileptr]:
            strs = strs + str(item) + ";"

        return strs.decode('gb2312').encode('utf-8')

    def generate_facts(self, factstr):
        """Generate fact file"""
        f = file(self.data_file_name, 'w+')
        f.writelines(factstr)
        f.close()

    def set_record_name(self):
        nowTime = datetime.datetime.now().strftime('%Y%m%d-%H%M%S')
        self.record_name = TEMP_FILE_PREFIX + 'record/ '+ nowTime + '.record'
        file = open(self.record_name, 'w')
        file.close()

    def get_dataframe_size(self):
        """Get the whole fact files' row size"""
        return len(self.dataframe)



    def get_result(self):
        self.engine.Reset()
        self.engine.LoadFacts(self.data_file_name)
        self.engine.Run()
        std_str = self.engine.StdoutStream.Read()
        # dlg_str = CLIPS_HPROSE.DialogStream.Read()
        # disp_str = CLIPS_HPROSE.DisplayStream.Read()

        # if not disp_str is None:
        #     disp_str = unicode(disp_str, 'gb2312').encode('utf-8')
        #     print disp_str
        # else:
        #     disp_str = 'NaN'
        #
        # if not dlg_str is None:
        #     dlg_str = unicode(dlg_str, 'gb2312').encode('utf-8')
        #     print dlg_str
        # else:
        #     dlg_str = 'NaN'

        if not std_str is None:
            pass
            # std_str = unicode(std_str, 'gbk').encode('utf-8')
            # print std_str
        else:
            std_str = 'NaN'

        # print std_str+'\n'

        fileobj = open(self.record_name, 'a')
        fileobj.writelines(std_str + '\n')
        return std_str

