python27 -m grpc_tools.protoc -I. --python_out=../proto_service --grpc_python_out=../proto_service ./dss.proto ./flight_control.proto ./comm_link.proto ./file.proto ./clips_facts.proto