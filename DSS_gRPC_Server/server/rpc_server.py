# _*_ coding: utf-8 _*_

import grpc
import dss_pb2_grpc
import time
from server_helper import Receiver
from concurrent import futures
import sys
reload(sys)
sys.setdefaultencoding('utf8')

_ONE_DAY_IN_SECONDS = 60 * 60 * 24




if __name__ == '__main__':
    server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
    dss_pb2_grpc.add_ReasoningServicer_to_server(Receiver(), server)

    server.add_insecure_port('[::]:50051')
    server.start()
    print('server start...')
    try:
        while True:
            time.sleep(_ONE_DAY_IN_SECONDS)
    except KeyboardInterrupt:
        server.stop(0)