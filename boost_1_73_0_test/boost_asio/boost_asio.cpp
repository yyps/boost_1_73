//
// timer.cpp
// ~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <iostream>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include <boost/bind/bind.hpp>

class printer
{
public:
	printer(boost::asio::io_context& io)
		: strand_(boost::asio::make_strand(io)),
		timer1_(io, boost::asio::chrono::seconds(1)),
		timer2_(io, boost::asio::chrono::seconds(1)),
		count_(0)
	{
		timer1_.async_wait(boost::asio::bind_executor(strand_,
			boost::bind(&printer::print1, this)));

		timer2_.async_wait(boost::asio::bind_executor(strand_,
			boost::bind(&printer::print2, this)));
	}

	~printer()
	{
		std::cout << "Final count is " << count_ << std::endl;
	}

	void print1()
	{
		if (count_ < 10)
		{
			std::cout << "Timer 1: " << count_ << std::endl;
			++count_;

			timer1_.expires_at(timer1_.expiry() + boost::asio::chrono::seconds(1));

			timer1_.async_wait(boost::asio::bind_executor(strand_,
				boost::bind(&printer::print1, this)));
		}
	}

	void print2()
	{
		if (count_ < 10)
		{
			std::cout << "Timer 2: " << count_ << std::endl;
			++count_;

			timer2_.expires_at(timer2_.expiry() + boost::asio::chrono::seconds(1));

			timer2_.async_wait(boost::asio::bind_executor(strand_,
				boost::bind(&printer::print2, this)));
		}
	}

private:
	boost::asio::strand<boost::asio::io_context::executor_type> strand_;
	boost::asio::steady_timer timer1_;
	boost::asio::steady_timer timer2_;
	int count_;
};

int main_01()
{
	boost::asio::io_context io;
	printer p(io);
	boost::thread t(boost::bind(&boost::asio::io_context::run, &io));
	io.run();
	t.join();

	return 0;
}

#include <boost/system/error_code.hpp>
#include "stdio.h"
#include <string>
using namespace boost::asio;
//using namespace boost::system;
namespace sys = boost::system;

typedef boost::shared_ptr<ip::tcp::socket> sock_ptr;
typedef boost::system::error_code syserr;
void con_handler(sys::error_code errc)
{
	printf("Call con_handler error:%d \n", errc.value());

	if (errc.value() == 0)
	{
		
	}
}

int main()
{
	io_service svr;
	ip::tcp::endpoint ep(ip::address::from_string("127.0.0.1"), 8501);

	int n = 1000;
	for (int i=0; i<n; ++i)
	{
		ip::tcp::socket sock(svr);
		syserr errc;
		sock.connect(ep, errc);
		if (errc)
		{
			printf("链接服务器失败: %d", errc.value());
			return 0;
		}

		std::string buf = "my name is guojianguang~!!";
		errc.clear();
		sock.write_some(buffer(buf), errc);
		char rbuf[512];

		printf("Conn %d OK! \n", i);
		/*	sock.read_some(buffer(rbuf), errc);
			if (errc)
			{
				printf("err:%d - %s", errc.value(), errc.message().c_str());
			}*/
	}
	

	int a;
	std::cin >> a;

//	sock.write_some()

//	sock.read
	
	return 0;
}