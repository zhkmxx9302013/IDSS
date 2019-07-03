from lstm_service import LstmService

class LstmServiceFactory:
    def __init__(self):
        self.obj = LstmService()
        pass

    def reset(self):
        self.obj.reset()
        pass

    def get_chart_data(self):
        self.obj.on_sim_trigger()
        pass