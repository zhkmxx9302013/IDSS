protoc -I ./ --grpc_out=../proto-gen --plugin=protoc-gen-grpc=grpc_cpp_plugin.exe clips_facts.proto comm_link.proto dss.proto flight_control.proto file.proto lstm_prediction.proto
protoc -I ./ --cpp_out=../proto-gen clips_facts.proto comm_link.proto dss.proto flight_control.proto file.proto lstm_prediction.proto
pause