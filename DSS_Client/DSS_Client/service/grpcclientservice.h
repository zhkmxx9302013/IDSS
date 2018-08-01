#ifndef GRPCCLIENTSERVICE_H
#define GRPCCLIENTSERVICE_H

#include <memory>
#include <string>
#include <vector>
#include <memory>
#include <map>
#include <grpc/grpc.h>
#include <grpc++/channel.h>
#include <grpc++/client_context.h>
#include <grpc++/create_channel.h>
#include <grpc++/security/credentials.h>


#include "proto-gen/dss.pb.h"
#include "proto-gen/dss.grpc.pb.h"
#include "proto-gen/comm_link.pb.h"
#include "proto-gen/clips_facts.pb.h"
#include "proto-gen/flight_control.pb.h"
#include "proto-gen/file.pb.h"

using namespace std;
using grpc::Channel;
using grpc::ClientAsyncResponseReader;
using grpc::ClientReader;
using grpc::ClientReaderWriter;
using grpc::ClientWriter;
using grpc::ClientContext;
using grpc::CompletionQueue;
using grpc::Status;

using buaa::dss::Reasoning;
using buaa::dss::placeholder;

using buaa::facts::fc_facts;
using buaa::facts:: comm_facts;
using buaa::facts::facts;
using buaa::facts::result;

using buaa::facts::flightcontrol::velocity;
using buaa::facts::flightcontrol::altitude;
using buaa::facts::flightcontrol::radio_altitude1;
using buaa::facts::flightcontrol::radio_altitude2;
using buaa::facts::flightcontrol::pressure_altitude;
using buaa::facts::flightcontrol::gear_state;
using buaa::facts::flightcontrol::coolant1;
using buaa::facts::flightcontrol::coolant2;

using buaa::facts::commlink::c_up;
using buaa::facts::commlink::c_down;
using buaa::facts::commlink::u_up;
using buaa::facts::commlink::u_down;
using buaa::facts::commlink::ku_up;
using buaa::facts::commlink::ku_down;

using buaa::facts::sim_start;
using buaa::facts::result;

using buaa::file::rule_file_chk;
using buaa::file::rule_file_info;
using buaa::file::fact_list;
using buaa::file::fact_file_info;
using buaa::file::fact_var;
using buaa::file::fact_file_chk;
using buaa::file::mapper;


class GrpcClientService
{
public:
    GrpcClientService();
    explicit GrpcClientService(std::shared_ptr<Channel> channel) : stub_(Reasoning::NewStub(channel)) {}
    void SetChannel(std::shared_ptr<Channel> channel);
    bool FetchRuleFileList(std::vector<rule_file_info> &filelist);//获取规则文件列表
    bool SaveRuleList(const std::vector<rule_file_chk> &filelist); //保存需要解析的规则库文件列表到服务端

    std::vector<std::map<std::string, std::string>> GetSlotList();  //获取全部的Slot列表
    bool SetSlotList(const std::vector<fact_list> &factlist); //通知服务端需要加载的Slot信息
    std::vector<fact_list> GetSelectedSlots(); //获取已选择的模板槽对象列表

    bool FetchFactList(std::vector<fact_file_info> &filelist); //获取事实列表
    bool FetchVarList(std::vector<fact_var> &vallist);//获取事实库中的可选变量
    bool SaveFactList(const std::vector<fact_file_chk> &filelist); //保存需要解析的事实库文件列表到服务端

    bool SetMapperList(const std::vector<buaa::file::mapper> &mapperList); //设置模板槽、变量映射关系到服务端

    void StartReasoning(); //开始推理
    buaa::facts::result GetReasoningResult(); //获取推理结果

    //unique_ptr成员的拷贝构造器
    GrpcClientService( const GrpcClientService& rhs ): stub_( copy_unique(rhs.stub_) )
    {
    }

    template< class T >
    std::unique_ptr<T> copy_unique(const std::unique_ptr<T>& source)
    {
        return source ? std::make_unique<T>(*source) : nullptr;
    }

private:
    //grpc::ClientContext context;
    std::unique_ptr<Reasoning::Stub> stub_;
};

#endif // GRPCCLIENTSERVICE_H
