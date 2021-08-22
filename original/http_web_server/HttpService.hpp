#ifndef HTTPSERVICE_HPP
#define HTTPSERVICE_HPP

#include <string>
#include <memory>
#include <boost/asio.hpp>

//http methods types
enum class HttpMethods{
  GET,
  HEAD,
  POST,
  PUT,
  DELETE,
  CONNECT,
  OPTIONS,
  TRACE,
};

//each http request returned by parser
struct HttpRequest
{
  HttpMethods method;
  std::string request;
  std::string resource;
  std::string http_version;
  unsigned int status;
};


class HttpRequestParser
{
  public:
    HttpRequestParser(std::string&);
    std::shared_ptr<HttpRequest> GetHttpRequest();

  private:
    std::string m_HttpRequest;
};


class HttpService
{
  public:
    HttpService(std::shared_ptr<boost::asio::ip::tcp::socket>);

    void HttpHandleRequest();
  
  private:
    std::string GetIp();
    void ProcessGetRequest();
    std::string GetCGIProgram(std::string);
    void ProcessPostRequest();
    void ExecuteProgram(std::string, std::string);
    void ProcessHeadRequest();
    void ProcessDeleteRequest();
    void ProcessOptionsRequest();
    std::string GetResponseStatus();
    void SendResponse();
    void Finish();

  private:
    std::shared_ptr<boost::asio::ip::tcp::socket> m_Socket;
    boost::asio::streambuf m_Request;
    std::string m_RequestedResource;
    std::unique_ptr<char[]> m_ResourceBuffer;
    unsigned int m_ResponseStatusCode;
    std::size_t m_ResourceSizeInBytes;
    bool m_IsResponseSent;
    std::string m_ServerOptions;
    std::string m_ScriptData;
    std::string m_ContentType;


    const std::string m_DefaultIndexPage = "<html>\n<head>\n<title>HTTP Web Server</title>\
        \n<style type=\"text/css\" media=\"screen\">\
          \nbody, html {padding: 3px 3px 3px 3px;background-color: #D8DBE2;\
            font-family: Verdana, sans-serif;font-size: 11pt;text-align: center;\
          }\ndiv.main_page{position: relative;display: table;width: 800px;margin-bottom: 3px;\
          margin-left: auto;margin-right: auto;padding: 0px 0px 0px 0px;border-width: 2px;\
          border-color: #616748;border-style: solid;background-color: #FFFFFF;text-align: center;\
          }\ndiv.page_header{height: 99px;width: 100%;background-color: #F5F6F7;}\
          \ndiv.page_header span{margin: 15px 0px 0px 50px;font-size: 180%;font-weight: bold;}\
          \ndiv.content_section_text{padding: 4px 8px 4px 8px;color: #000000;font-size: 100%;\
          }\ndiv.section_header{padding: 3px 6px 3px 6px;background-color: #8E9CB2;color: #FFFFFF;\
          font-weight: bold;font-size: 112%;text-align: center;}div.section_header_blue {\
          background-color: #4A64DA;}\n.floating_element{position: relative;float: center;}\
          </style>\n</head>\n<body><br/><div class=\"main_page\"><div class=\"page_header floating_element\">\
          <span class=\"floating_element\"><br/>HTTP Web Server</span></div>\
          <div class=\"content_section floating_element\">\
          <div class=\"section_header section_header_blue\"><div id=\"about\"></div>It works!</div>\
          <div class=\"content_section_text\"><br/><p>\
          This is the default welcome page used to test the correct operation of the HTTP Web Server.\
          <br>If you can read this page, it means that the HTTP Web server at this site is working properly.\
          <br>You should <b>replace this file</b> (located at\
          <tt>the provided path when server is started /index.html</tt>)\
          before continuing to operate your HTTP server.\
          <br>Request the static HTML page with Server IP and port <b>1234</b>.\
          <br>Request the PHP script and get it's the interpreted contents.\
          </p><br><a style=\"text-decoration:none;\"\
          href=\"https://github.com/pritamzope/http_web_server/\">\
          https://github.com/pritamzope/http_web_server/</a><br><br>\
          </div></div></div>\n</body>\n</html>";


};


#endif
