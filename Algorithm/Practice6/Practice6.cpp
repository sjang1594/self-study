#include <iostream>
#include <string>
#include <unordered_map>

class URLService
{
public:
    using actualURL = std::string;
    using tinyURL = std::string;
    
    std::pair<bool, actualURL> lookup(const tinyURL& url) const
    {
        auto it = data.find(url);
        if (it != data.end())
            return std::make_pair(true, it->second);
        return std::make_pair(false, std::string());
    }

	bool registerURL(const actualURL& actualUrl, const tinyURL& tinyUrl)
	{
		auto it = lookup(tinyUrl).first;
		if (!it)
		{
			data[tinyUrl] = actualUrl;
			return true;
		}
		return false;
	}

	bool deregisterURL(const tinyURL& tinyURL)
	{
		auto found = lookup(tinyURL).first;
		if (found)
		{
			data.erase(tinyURL);
			return true;
		}

		return false;
	}

    std::unordered_map< tinyURL, actualURL> data;
};

int main()
{
    URLService service;
	if (service.registerURL("https://www.gilbut.co.kr/book/view?bookcode=BN002245", "https://py_dojang"))
	{
		std::cout << "https://py_dojang 등록" << std::endl;
	}
	else
	{
		std::cout << "https://py_dojang 등록 실패" << std::endl;
	}

	if (service.registerURL("https://www.gilbut.co.kr/book/view?bookcode=BN001484", "https://c_dojang"))
	{
		std::cout << "https://c_dojang 등록" << std::endl;
	}
	else
	{
		std::cout << "https://c_dojang 등록 실패" << std::endl;
	}

	if (service.registerURL("https://www.gilbut.co.kr/book/view?bookcode=BN002402", "https://opencv4"))
	{
		std::cout << "https://opencv4 등록" << std::endl;
	}
	else
	{
		std::cout << "https://opencv4 등록 실패" << std::endl;
	}

	auto pythonBook = service.lookup("https://py_dojang");
	if (pythonBook.first)
	{
		std::cout << "https://py_dojang 원본 URL: " << pythonBook.second << std::endl;
	}
	else
	{
		std::cout << "https://py_dojang 원본 URL을 찾을 수 없습니다." << std::endl;
	}

	return 0;
}