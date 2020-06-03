#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/system/error_code.hpp>
#include <string>
#include <boost/filesystem/fstream.hpp>
#include <string>
#include <list>

using namespace std;
using namespace boost::filesystem;
namespace fs = boost::filesystem;

void DirItreation(path& p)
{
	do 
	{
		boost::system::error_code ec;
		if (!exists(p))
		{
			cout << "Path not exist!" << p.string() << endl;
			break;
		}

		if (!is_directory(p))
		{
			cout << "Path is not a directory!" << p.string() << endl;
			break;
		}

		cout << ">>>>>> Enter Path: " << p.string() << endl;

		for (auto& de : directory_iterator(p, ec))
		{
			path _p = de.path();
			if (is_directory(_p))
			{
				DirItreation(_p);
			}
			else
			{
				cout << "Iteration file: " << _p.string() << endl;
			}
		}
	} while (0);

	/*
	* path 拆分拼接基本操作
	*/
}

int main()
{
    /*
    * file_size函数的两种返回错误方式 
    * 1. 通过boost::system::error_code返回，通过第二个参数传出参 < file_size(_path, ec) >
    * 2. 通过try-catch方式获取 filesystem_error& e  < file_size(_path) >
    */
    do 
    {

		break;

		try
		{
			boost::system::error_code ec;
			path _path("e:\\myCode\\file_test\\Windows Server 2012-s011.vmdk");
			cout << "File is_complete " << _path.is_complete() << endl;
			cout << "File is_absolute " << _path.is_absolute() << endl;
			cout << "File is_relative " << _path.is_relative() << endl;
			if (!exists(_path))
			{
				cout << "File not exist" << endl;
				break;
			}

			if (is_regular_file(_path, ec))
			{
				cout << "File is regular file" << endl;
			}
			else if (is_directory(_path))
			{
				cout << "File is directory" << endl;
				
			}
			else
			{

			}

			std::cout << "File: " << _path.string()
				<< " Size: " << file_size(_path, ec) << endl;
			if (ec.value() != 0)
			{
				cout << "Error code: " << ec.value() << endl;
			}
		}
		catch (filesystem_error& e)
		{
			cout << "Error code: " << e.code().value() << endl;
			cout << e.what() << endl;
		}
    } while (0);



	/*
	* 文件夹遍历
	*/
	do 
	{
		break;
		try
		{
			boost::system::error_code ec;
			path _path("e:\\myCode\\file_test\\");
			DirItreation(_path);

		}
		catch (filesystem_error& e)
		{
			cout << "Error code: " << e.code().value() << endl;
			cout << e.what() << endl;
		}
	} while (0);


	/*
	* Unicode支持, 拼接解析基本操作
	* / 自动添加\, += 操作符只是简单的字符串拼接
	*/

	do 
	{

		path ret;
		path p("e:/mycode/file_test");

		{
			// / 操作符
			ret = p / path("APP");
			cout << "append src: " << p.string() << endl;

			// += 操作符
			ret = p += path("\\APP");
			cout << "Add src: " << p.string() << endl;

		}

		{
			// 根据当前系统修改 \\ 或者 / 分隔符
			ret = p.make_preferred();
			cout << "make_preferred" << ret.string() << endl;

			// 移除文件名 或者 最后一层目录
			ret = p.remove_filename();
			cout << "remove_filename " << ret.string() << endl;

			// 替换后缀名，也可以加点
			ret = p.replace_extension("bat");
			cout << "replace_extension " << ret.string() << endl;
			ret = ret.replace_extension(".b2t");
			cout << "replace_extension " << ret.string() << endl;

			// 生成POSIX / 分隔符的字符串 
			path p2("e:/mycode\\file_test\\22\\33.tt");
			cout << "generic_string " << p2.generic_string() << endl;

			// 比较 0 表示两者一致
			path p3("e:/mycode\\file_test\\22\\3ddd3.tt");
			path p4("e:/mycode\\file_test\\22\\3ddd3.tt");
			cout << "compare  " << p4.compare(p3) << endl;

			// 属性 同时带有 has_xxx的查询方法
		//	path p5("e:/mycode/file_test\\22\\3ddd3.tt");
			path p5("/mycode/file_test\\22\\3ddd3.tt");
			cout << "The path: " << p5 << endl;
			cout << "root_name " << p5.root_name() << endl;
			cout << "root_directory " << p5.root_directory() << endl;
			cout << "root_path " << p5.root_path() << endl;
			cout << "relative_path " << p5.relative_path() << endl;
			cout << "parent_path " << p5.parent_path() << endl;
			cout << "filename " << p5.filename() << endl;
			cout << "stem " << p5.stem() << endl;
			cout << "extension " << p5.extension() << endl;

			// is_xxx
			cout << "is_absolute " << p5.is_absolute() << endl;
			cout << "is_relative " << p5.is_relative() << endl;
			cout << "empty " << p5.empty() << endl;
			/*
			path t = p5.root_path();
			if (!t.empty())
			{
				// t... do something
			}
			*/

			// 路径迭代
			{
				cout << "-------------------------- " << endl;
				cout << p5 << "迭代结果: " << endl;
				path::iterator itr = p5.begin();
				for (; itr != p5.end(); ++itr)
				{
					cout << (*itr).string() << endl;
				}
				cout << "-------------------------- " << endl;
			}

			// 文件名 / 路径 可移植 有效性检测
			{
				string path_n("1.x");
				string path_p("bbcc");
				cout << "The path: " << path_n << endl;

				// poxis 符合
				cout << "portable_posix_name " << portable_posix_name(path_n) << endl;
				
				// win 符合
				cout << "windows_name " << windows_name(path_n) << endl;

				// win & poxis都要符合
				cout << "portable_name " << portable_name(path_n) << endl;

				// 目录名
				cout << "portable_directory_name " << portable_directory_name(path_p) << endl;
		
				cout << "-------------------------- " << endl;
			}

			// 文件 status file_type & perm 权限
			{
				boost::system::error_code ec;
				path path_d("e:\\mycode\\file_test\\Windows Server 2012-s011.vmdk");
				file_status fs = status(path_d, ec);
				cout << "file_type: " << fs.type() << endl;
				cout << "permissions: " << fs.permissions() << endl;
				
				cout << "is_directory" << is_directory(path_d) << endl;
				cout << "is_regular_file" << is_regular_file(path_d) << endl;

				path path_d2("e:\\mycode\\file_test\\EMPTY.txt");

				cout << "Windows Server 2012-s011.vmdk is_empty" << fs::is_empty(path_d, ec) << endl;
				cout << "path_d2 is_empty" << fs::is_empty(path_d2, ec) << endl;

				cout << "-------------------------- " << endl;
			}	

			{
				boost::system::error_code ec;
				// 程序初始工作目录 只读
				cout << "initial_path " << initial_path() << endl;

				// 程序当前工作目录, 本函数也可以更改工作目录
				cout << "current_path " << current_path() << endl;
				current_path("E:\\_work", ec);
				cout << "after change current_path " << current_path() << endl;
			
				// 磁盘剩余空间 (字节数)
				const int GB = 1024 * 1024 * 1024;
				space_info si;
				path e("c:\\");
				si = space(e, ec);
				if (ec.value() == 0)
				{
					cout << e.string() << "free: " << si.free / GB
						<< "available: " << si.available / GB 
						<< "capacity: " << si.capacity / GB << endl;
				}

				path tt("../fo");
				// 获取绝对路径 智能转换 - 建议使用
				cout << "system_complete: " << system_complete(tt) << endl;
				// 简单拼接 - 不建议使用
				cout << "absolute: " << absolute(tt) << endl;
				
			}
		}
	} while (0);


	/*
	* 拷贝、删除文件
	*/
	do 
	{

		path src("d:\\111.rar");
		path dst("d:\\recc\\2a\\4b\\5g\\6l");
	//	path dstf("d:\\recc\\2.rar");
		boost::system::error_code err;
		if (!exists(dst, err))
		{
			if (!create_directories(dst, err))
			{
				cout << "Dest dir err " << err.value() << endl;
				break;
			}

		}

		dst /= path("2.rar");
		copy_file(src, dst, copy_option::overwrite_if_exists, err);
		if (err.value() == 0)
		{
			fs::remove(src, err);
		}
		
	} while (0);


	/*
	{
		// \u263A is "Unicode WHITE SMILING FACE = have a nice day!"
		std::string narrow_string("smile2");
		std::wstring wide_string(L"smile2\u263A");
		std::list<char> narrow_list;
		narrow_list.push_back('s');
		narrow_list.push_back('m');
		narrow_list.push_back('i');
		narrow_list.push_back('l');
		narrow_list.push_back('e');
		narrow_list.push_back('3');
		std::list<wchar_t> wide_list;
		wide_list.push_back(L's');
		wide_list.push_back(L'm');
		wide_list.push_back(L'i');
		wide_list.push_back(L'l');
		wide_list.push_back(L'e');
		wide_list.push_back(L'3');
		wide_list.push_back(L'\u263A');

		{ fs::ofstream f("smile"); }
		{ fs::ofstream f(L"smile\u263A"); }
		{ fs::ofstream f(narrow_string); }
		{ fs::ofstream f(wide_string); }
		{ fs::ofstream f(narrow_list); }
		{ fs::ofstream f(wide_list); }
		narrow_list.pop_back();
		narrow_list.push_back('4');
		wide_list.pop_back();
		wide_list.pop_back();
		wide_list.push_back(L'4');
		wide_list.push_back(L'\u263A');
		{ fs::ofstream f(fs::path(narrow_list.begin(), narrow_list.end())); }
		{ fs::ofstream f(fs::path(wide_list.begin(), wide_list.end())); }
	}
	*/
}