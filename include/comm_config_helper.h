#ifndef __COMM_CONFIG_HELPER_H_8011__
#define __COMM_CONFIG_HELPER_H_8011__
#include <string>
#include <vector>
#include <sstream>
#include "comm_base.h"
#include "comm_configdocument.h"
using namespace std;
namespace comm
{
    //�������нӿڣ�������׳��쳣
	//֧�ֵĸ�ʽ 
	//[comm]
	//count = 0
    class CConfigHelper: public CCommBase, public CConfigDocument
    {
        public:
            CConfigHelper(const char* etcfile):CConfigDocument(etcfile){}
        
        public:
			bool ExistItem(const char* prefix)throw(CCommException);
            /*�ܽ����ĸ�ʽ:
            * server_1=10.128.0.44:8839  ��Ӧ����:prefix = server_  posindex=1   
            */
            void GetIPandPort(const char* prefix, int posindex, std::string& out_ip, unsigned& port, char delimiter = ':')throw(CCommException);       
            /*�ܽ����ĸ�ʽ:
            * ip_2 = 10.128.0.44    ��Ӧ����:prefix = ip_  posindex=2
            */
            std::string& GetString(const char* prefix, int posindex)throw(CCommException);
            std::string& GetString(const char * prefix)throw(CCommException);
            /*�ܽ����ĸ�ʽ:
            * port_4 = 8201  ��Ӧ����:prefix = port_  posindex=4
            */
            int GetInt(const char* prefix, int posindex)throw(CCommException);

            int GetInt(const char* prefix)throw(CCommException);
			/// <summary>
			/// 
			/// </summary>
			/// <param name="prefix"></param>
			/// <returns></returns>
			bool GetBoolean(const char* prefix, int posindex)throw(CCommException);
			/// <summary>
			/// 
			/// </summary>
			/// <param name="prefix"></param>
			/// <returns></returns>
			bool GetBoolean(const char* prefix)throw(CCommException);
			
            void SplitString(const char* prefix, int posindex, vector<string>& out_sp, const char* delimiters)throw(CCommException);

            void SplitString(const char* prefix, vector<string>& out_sp, const char* delimiters)throw(CCommException);

			template<typename T>
			T Get(const char* prefix, int posindex)throw(CCommException);
			template<typename T> 
			T Get(const char* prefix)throw(CCommException);
            /*�ܽ����ĸ�ʽ 
            * ttc.uinrang_1 = 82-84  ��Ӧ������prefix ttc.uinrang_1
            * Container��֧��vector,set
            */ 
            template<typename Container>
            void SplitInt(const char* prefix, Container& out_sp)throw(CCommException);
            template<typename Container>
            void SplitInt(const char* prefix, int posindex, Container& out_sp)throw(CCommException);
        protected:
            char m_buf[128];
    };
    template<typename Container>
    void CConfigHelper::SplitInt(const char* prefix, int posindex, Container& out_sp)throw(CCommException)
	{
		snprintf(m_buf, sizeof(m_buf), "%s%d", prefix, posindex);
		SplitInt(m_buf, out_sp);
	}
	template<typename Container>
	void CConfigHelper::SplitInt(const char* prefix, Container& out_sp)throw(CCommException)
	{
		std::string _s = (*this)[prefix];
		if(_s.empty())
		{
			THROW_EX("%s not exist!", prefix);
		}
		char* _str = (char*)_s.c_str();
		//TRACE("total string:%s", _str);
		do
		{
			while(*_str && !isdigit(*_str))
				++_str;
			if(*_str == 0)break;
			out_sp.insert(out_sp.end(), strtoul(_str, &_str, 0));
			//TRACE("current string:%s number-dec:%u", _str, out_sp.back());
		} while(*_str);
	}
	template<typename T> 
	T CConfigHelper::Get(const char* prefix, int posindex)throw(CCommException)
	{
		snprintf(m_buf, sizeof(m_buf), "%s%d", prefix, posindex);
		return Get<T>(m_buf);
	}
	template<typename T> 
	T CConfigHelper::Get(const char* prefix)throw(CCommException)
	{
		std::string _s = (*this)[prefix];
		if(_s.empty())
		{
			THROW_EX("%s not exist!", prefix);
		}
		istringstream iss(_s);
		T _value;
		iss >> _value;
		return _value;
	}
}
#endif


