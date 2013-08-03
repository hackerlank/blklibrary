#ifndef __COMM_UIN_H_8000__
#define __COMM_UIN_H_8000__
#include <stdio.h>
#include <set>
#include <string>
#include "comm_macro.h"
#include "comm_base.h"
namespace comm
{
    using namespace std;
	class CUin:public CCommBase
	{
        public:
            CUin():m_fp(NULL){}
            CUin(int fd);
            inline CUin(const char* uinfile):m_fp(NULL){SetUinFile(uinfile);}
            inline CUin(string& uinfile):m_fp(NULL){SetUinFile(uinfile.c_str());}
            ~CUin();
		public:
            int SetUinFile(const char* uinfile);
            inline int SetUinFile(string& uinfile){return SetUinFile(uinfile.c_str());}
            
            //���ļ�<ÿ��һ��uin>�л�ȡUin,����uin������Ч���ж�
            //����RTN_ERROR����ʾ�ļ����ݶ��꣬������
            //����RTN_SUCCESS,��ʾ��ȡ�ɹ�
            bool GetNextUin(unsigned &uin);
            
            //����RTN_ERROR����ʾ�ļ����ݶ���,������
            //����RTN_SUCCESS,��ʾ��ȡ�ɹ�
            bool BatchGetUins(set<unsigned>& sets, const unsigned needcnt);
        protected:
            string m_uinfile;
            FILE* m_fp;
            char m_buf[64];
	};
}
#endif

