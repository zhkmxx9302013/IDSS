# import rule_controller
import clips
import json
import clips_service as cs
from common_utils import *
import pandas as pd


# rc = rule_controller.rule_controller()


filelist = ['test.csv', 'test2.csv']

# dataframe = pd.DataFrame
dataframe = pd.read_csv(FACT_FILE_PREFIX + 'test.csv')
# dataframe1 = pd.read_csv(FACT_FILE_PREFIX + 'test.csv')
print(str(dataframe.iloc[0]))

strs = ""
for item in dataframe.iloc[0]:
    strs = strs + str(item) + ";"

print strs.decode('gb2312').encode('utf-8')
# dataframe2 = pd.read_csv(FACT_FILE_PREFIX + 'test2.csv')
# dataframe = pd.concat([dataframe1, dataframe2], axis=1, join='inner')

# print('(' + dataframe['HeightWatch1'][0].decode('gb2312').encode('utf8') + ")")

# css = cs.clips_service()
# css.load_fact_file(filelist)
# print (css.generate_fact_str(0))


# lists = rc.parse_rulelist(filelist)
# print(rc.parse_rulelist(filelist))

# engine = clips.Environment()
# engine.Reset()
# engine.Clear()
# engine.Load(RULE_FILE_PREFIX + 'comm_link_rules.clp')
# engine.Load(RULE_FILE_PREFIX + 'flight_control_rules.clp')
# print engine.FindTemplate(lists[0])
# print engine.TemplateList()
# print ''
# print engine.PrintTemplates()


# engine = clips.Environment()
# clips.Reset()
# clips.Clear()
# # clips.Load(RULE_FILE_PREFIX + 'comm_link_rules.clp')
# clips.Load(RULE_FILE_PREFIX + 'flight_control_rules.clp')
#
# slot_dict = {}
# for template_name in clips.TemplateList():
#     template = clips.FindTemplate(template_name)
#     print template
#     if len(template.Slots.Names()) > 0:
#         slot_dict[template] = template.Slots.Names()
#
# for key, value in slot_dict.items():
#     print key, ':'
#     for item in value:
#         print str(item)

        # print (item.Slots.Names() for item in clips.TemplateList()).next()

# @test
# with open(FACT_FILE_PREFIX + 'desc.json', 'r') as file:
#     json_obj = json.load(file)
#     print json_obj.has_key('test2.csv')
#     # print file_desc
#     file.close()
