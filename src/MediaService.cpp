#include "MediaService.h"
#include "mk_events.h"
#include "mk_media.h"
#include "mk_common.h"
#include "mk_util.h"

bool MediaService::Start()
{
    // char *ini_path = mk_util_get_exe_dir("config.ini");
    // mk_config config = {
    //         .ini = ini_path,
    //         .ini_is_path = 1,
    //         .log_level = 0,
    //         .log_mask = LOG_CONSOLE,
    //         .log_file_path = NULL,
    //         .log_file_days = 0,
    //         .ssl = NULL,
    //         .ssl_is_path = 1,
    //         .ssl_pwd = NULL,
    //         .thread_num = 0
    // };
    // mk_env_init(&config);
    // mk_free(ini_path);

    // // 启动rtsp服务器监听，并开始监听对应事件
    // mk_rtsp_server_start(554, 0);
    // mk_events events = {
    //         .on_mk_media_changed = nullptr,
    //         .on_mk_media_publish = nullptr,
    //         .on_mk_media_play = nullptr,
    //         .on_mk_media_not_found = nullptr,
    //         .on_mk_media_no_reader = nullptr,
    //         .on_mk_http_request = nullptr,
    //         .on_mk_http_access = nullptr,
    //         .on_mk_http_before_access = nullptr,
    //         .on_mk_rtsp_get_realm = nullptr,
    //         .on_mk_rtsp_auth = nullptr,
    //         .on_mk_record_mp4 = nullptr,
    //         .on_mk_shell_login = nullptr,
    //         .on_mk_flow_report = nullptr
    // };
    // mk_events_listen(&events);

    return true;
}

bool MediaService::Stop()
{
    mk_stop_all_server();
    return true;
}
