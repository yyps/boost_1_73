#include <iostream>
#include <boost/asio.hpp>
#include <boost/system/error_code.hpp>
#include <boost/bind.hpp>
#include <vector>
using namespace boost::asio;


/*
* ASIO Server demo
*/
typedef boost::shared_ptr<ip::tcp::socket> sock_ptr;
typedef boost::shared_ptr<ip::tcp::acceptor> acpt_ptr;
typedef boost::system::error_code syserr;
io_service svr;
std::vector<sock_ptr> conn;
int cnt = 0;
void handle_accept(acpt_ptr acp, sock_ptr scp, boost::system::error_code errc)
{
    do 
    {
        if (!errc)
        {
            ip::tcp::endpoint ep = scp->remote_endpoint();
            syserr err;
            printf("收到一个客户链接: %d %s \n", cnt++, ep.address().to_string(err).c_str());

            char buf[512] = { 0 };
            syserr errc;
            scp->read_some(buffer(buf), errc);
            if (!errc)
            {
                printf("收到客户链接: %s 的内容:%s \n", ep.address().to_string(err).c_str(), buf);
            }
            conn.push_back(scp);
        }
        else
        {
            printf("接收客户都安链接错误: %d, 原因: %s \n", errc.value(), errc.message().c_str());
            break;
        }

        sock_ptr sock(new ip::tcp::socket(svr));
        acp->async_accept(*sock, boost::bind(handle_accept, acp, sock, _1));
        
    } while (0);
}


int main()
{
    ip::tcp::endpoint edpt(ip::tcp::v4(), 8501);
    acpt_ptr acptor(new ip::tcp::acceptor(svr, edpt));
    sock_ptr sock(new ip::tcp::socket(svr));
    acptor->async_accept(*sock, boost::bind(handle_accept, acptor, sock, _1));
    svr.run();
    
    return 0;
}