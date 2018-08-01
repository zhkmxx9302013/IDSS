#include "grpcclientservice.h"
#include <iostream>
using namespace std;
GrpcClientService::GrpcClientService()
{

}

//@stub 获取规则库文件列表
bool GrpcClientService::FetchRuleFileList(vector<rule_file_info> &fileList)
{
    buaa::dss::placeholder ph;
    buaa::file::rule_file_info file;
    grpc::ClientContext context;
    if(fileList.size() > 0) fileList.clear();

    try{
         std::unique_ptr<ClientReader<rule_file_info>> fileListReader(stub_->GetRuleFile(&context, ph));
         while(fileListReader->Read(&file))
         {
             fileList.emplace_back(file);
         }

    }catch(const std::exception& e){
        return false;
    }
    return true;
}

//@stub 加载所选的规则文件列表
bool GrpcClientService::SaveRuleList(const vector<rule_file_chk> &filelist)
{
    if(filelist.size() <= 0) return false;
    grpc::ClientContext context;
    buaa::dss::placeholder ph;

    try{
        std::unique_ptr<ClientWriter<rule_file_chk>> fileListWriter(stub_->LoadRuleFile(&context, &ph));
        for(auto file : filelist)
        {
            if(!fileListWriter->Write(file))
            {
                cerr << "werr" <<endl;
                break;
            }
        }
        fileListWriter->WritesDone();

        Status status = fileListWriter->Finish();
        if(status.ok())return true;
        else return false;

    }catch(const std::exception& e){
        return false;
    }
    return true;
}

//@stub 保存需要解析的事实库文件列表到服务端
bool GrpcClientService::SaveFactList(const vector<fact_file_chk> &filelist)
{
    if(filelist.size() <= 0) return false;
    grpc::ClientContext context;
    buaa::dss::placeholder ph;

    try{
        std::unique_ptr<ClientWriter<fact_file_chk>> fileListWriter(stub_->LoadFactFile(&context, &ph));
        for(auto file : filelist)
        {
            if(!fileListWriter->Write(file))
            {
                cerr << "werr" <<endl;
                break;
            }
        }
        fileListWriter->WritesDone();

        Status status = fileListWriter->Finish();
        if(status.ok())return true;
        else return false;

    }catch(const std::exception& e){
        return false;
    }
    return true;
}

//@stub 返回slots列表<templatename, slotname>
std::vector<std::map<std::string, std::string>>  GrpcClientService::GetSlotList()
{
    std::vector<std::map<std::string, std::string>> slot_list;
    buaa::dss::placeholder ph;
    buaa::file::fact_list fact;
    grpc::ClientContext context;

    try{
         std::unique_ptr<ClientReader<fact_list>> factListReader(stub_->GetFactSlots(&context, ph));
         while(factListReader->Read(&fact))
         {
             std::map<std::string, std::string> slot_map;
             slot_map.insert(std::pair<std::string, std::string>(fact.template_name(), fact.slot_name()));
             slot_list.emplace_back(slot_map);
         }

    }catch(const std::exception& e){
        return { };
    }
    return slot_list;
}

//@stub 通知服务端需要加载的Slot信息(只传template名称即可)
bool GrpcClientService::SetSlotList(const vector<fact_list> &factlist)
{
    if(factlist.size() <= 0) return false;
    grpc::ClientContext context;
    buaa::dss::placeholder ph;

    try{
        std::unique_ptr<ClientWriter<fact_list>> factListWriter(stub_->SetFactSlots(&context, &ph));
        for(auto fact : factlist)
        {
            if(!factListWriter->Write(fact))
            {
                cerr << "werr" <<endl;
                break;
            }
        }
        factListWriter->WritesDone();

        Status status = factListWriter->Finish();
        if(status.ok())return true;
        else return false;

    }catch(const std::exception& e){
        return false;
    }
    return true;
}


bool GrpcClientService::FetchFactList(vector<fact_file_info> &fileList)
{
    buaa::dss::placeholder ph;
    buaa::file::fact_file_info file;
    grpc::ClientContext context;
    if(fileList.size() > 0) fileList.clear();

    try{
         std::unique_ptr<ClientReader<fact_file_info>> fileListReader(stub_->GetFactFile(&context, ph));
         while(fileListReader->Read(&file))
         {
             fileList.emplace_back(file);
         }

    }catch(const std::exception& e){
        return false;
    }
    return true;
}

//@stub 获取已选择的模板槽对象列表
std::vector<fact_list> GrpcClientService::GetSelectedSlots()
{
    buaa::dss::placeholder ph;
    std::vector<fact_list> factList;
    fact_list fact;
    grpc::ClientContext context;

    try{
         std::unique_ptr<ClientReader<fact_list>> factListReader(stub_->GetSelectedSlots(&context, ph));
         while(factListReader->Read(&fact))
         {
             factList.emplace_back(fact);
         }

    }catch(const std::exception& e){
        return { };
    }
    return factList;
}

//@stub 获取事实库文件变量列表
bool GrpcClientService::FetchVarList(vector<fact_var> &vallist)
{
    buaa::dss::placeholder ph;
    buaa::file::fact_var fvar;
    grpc::ClientContext context;
    if(vallist.size() > 0) vallist.clear();

    try{
         std::unique_ptr<ClientReader<fact_var>> varListReader(stub_->GetVariableList(&context, ph));
         while(varListReader->Read(&fvar))
         {
             vallist.emplace_back(fvar);
         }

    }catch(const std::exception& e){
        return false;
    }
    return true;
}


//@stub 设置模板槽、变量映射关系到服务端
bool GrpcClientService::SetMapperList(const std::vector<buaa::file::mapper> &mapperList)
{
    if(mapperList.size() <= 0) return false;
    grpc::ClientContext context;
    buaa::dss::placeholder ph;

    try{
        std::unique_ptr<ClientWriter<buaa::file::mapper>> mapperListWriter(stub_->SetMappingList(&context, &ph));
        for(auto mapper : mapperList)
        {
            if(!mapperListWriter->Write(mapper))
            {
                cerr << "werr" <<endl;
                break;
            }
        }
        mapperListWriter->WritesDone();

        Status status = mapperListWriter->Finish();
        if(status.ok())return true;
        else return false;

    }catch(const std::exception& e){
        return false;
    }
    return true;
}


void GrpcClientService::StartReasoning() //开始推理
{
    grpc::ClientContext context;
    buaa::dss::placeholder ph;
    buaa::facts::sim_start sim;
    sim.set_start(true);
    try{
        Status status = stub_->StartReasoning(&context, sim, &ph);
        if (! status.ok())
            return;

    }catch(const std::exception& e){
        return;
    }
}

buaa::facts::result GrpcClientService::GetReasoningResult() //获取推理结果
{
    grpc::ClientContext context;
    buaa::dss::placeholder ph;
    buaa::facts::result res;

    try{
        Status status = stub_->GetReasoningResult(&context, ph, &res);
        if (status.ok())
            return res;
        else
            return {};

    }catch(const std::exception& e){
        return {};
    }
}

// 为桩设置channel
void GrpcClientService::SetChannel(std::shared_ptr<Channel> channel)
{
    this->stub_ = Reasoning::NewStub(channel);
}
