import json
import time

class BaseController:
    """
     @Interface class: need to be impl
    """
    def __init__(self):
        pass

    def on_sim_start(self):
        """
        Interface
        :return:
        """
        pass

    def time_stamp2time(self, timestamp):
        ts = time.localtime(timestamp)
        return time.strftime('%Y-%m-%d %H:%M:%S', ts)

    def get_filedesc(self, prefix, filename):
        with open(prefix + 'desc.json', 'r') as file:
            json_obj = json.load(file)
            if json_obj.has_key(filename):
                file_desc = json_obj[filename]
            else:
                file_desc = ''
            file.close()
            return file_desc