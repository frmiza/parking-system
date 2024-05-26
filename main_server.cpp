#include <Network/SwLibNet.hpp>
#include <Json/JsonHdrLib.hpp>
#include <Shared/env.hpp>

using namespace std;

int main(int argc, char const *argv[])
{
    JHR::JsonConfSvr* json_conf = new JHR::JsonConfSvr();
    json_conf->treat_json_file(SERVER_CONF_JSON);
    SW::ServerCentral* cc = new SW::ServerCentral(3,json_conf->get_svr_port());
    return 0;
}