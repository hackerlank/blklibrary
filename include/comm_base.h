/******************************************************************************
 * comm_base.h - ������Ļ��༰�����쳣��Ķ���
 * 
 * Copyright 2009-2009 Tencent Co.,Ltd.
 * 
 * DESCRIPTION: - 
 *     ������Ļ��༰�����쳣��Ķ���,����ʱ����ϱ���ѡ��:-rdynamic �쳣������ջ��Ϣ
 *     �����쳣��ʹ�ü�����:
 *     �쳣�Ҷ���Ϊͨ����ʱ�ȴ������ԡ��ͷ��ڴ桢�������Դ�ķ������Ϳ��Խ���������
 *     ����״̬��ʣ���״̬
 * modification history
 * --------------------
 * 01a, 2009-dec-17, comm written
 * --------------------
 ******************************************************************************/
#ifndef  __COMM_BASE_H_8005__
#define __COMM_BASE_H_8005__
#include <exception>
#include <stdarg.h>
#include <execinfo.h>
#include <string>
#include <time.h>
#include <libgen.h>
#include <sstream>
namespace comm
{
    /*�궨�� */
    //�׳��쳣��Ϣ
    #define __OFILE__ basename((char*)__FILE__)
    #ifdef DEBUG
    #define THROW_EX(fmt, msg...) do{ \
      printf("[%s %s %s %d]" fmt "\n", comm::utility::GetTimeStr(), __OFILE__, __FUNCTION__, __LINE__, ##msg); \
      throw comm::CCommException("[%s %s %s %d]" fmt, \
      utility::GetTimeStr(), __OFILE__, __FUNCTION__, __LINE__, ##msg);}while(0)

    #define THROW_CODE_EX(code, fmt, msg...) do{ \
      printf("[%s %s %s %d code:%d]" fmt  "\n", utility::GetTimeStr(), __OFILE__, __FUNCTION__, __LINE__, (code), ##msg); \
      throw comm::CCommException((code), "[%s %s %s %d]" fmt, \
      comm::utility::GetTimeStr(), __OFILE__, __FUNCTION__, __LINE__, ##msg);}while(0)

    #define THROW_ERRINFO(fmt, msg...) do{ \
      printf(fmt  "\n", ##msg); \
      throw comm::CCommException(fmt, ##msg);}while(0)

    #define RETHROW_RETCODE(retcode, ex) throw comm::CCommException((ex).what_string(), retcode)
    #else
    #define THROW_EX(fmt, msg...) throw comm::CCommException("[%s %s %s %d]" fmt,  \
        comm::utility::GetTimeStr(), __OFILE__, __FUNCTION__, __LINE__, ##msg)
        
    #define THROW_CODE_EX(code, fmt, msg...) throw comm::CCommException((code), "[%s %s %s %d]" fmt,  \
        comm::utility::GetTimeStr(), __OFILE__, __FUNCTION__, __LINE__, ##msg)

    #define THROW_ERRINFO(fmt, msg...) throw comm::CCommException(fmt, ##msg)

    #define RETHROW_RETCODE(retcode, ex) throw comm::CCommException((ex).what_string(), retcode)
    #endif
    /*end*/

    enum Errcode
    {
        RTN_WARN           = -10,
        RTN_ERROR          = -20,
        RTN_SUCCESS        = 0,
        RTN_INFO           = 5
    };
    class CCommBase
    {
        public:
            virtual ~CCommBase(){};
            inline const char* GetLastErrmsg(){return m_errmsg.c_str();}
            virtual const char* ToString(){return NULL;}
        protected:
            std::string m_errmsg;
    };
    //null object
    class NullObj{
    public:
        static std::string className()
        {
            return "NullObj";
        }
        std::ostream& display(std::ostream& _os, int =0) const
        {
            return _os << "NullObj";
        }
        std::ostream& displaySimple(std::ostream& _os, int =0) const
        {
            return _os << "NullObj";
        }
    };

    template <typename T>
    class CSingleton 
    {
        public:
            static inline T& instance(){return log;}
        private:
            static T log;
    };
    
    template<typename T> 
    T CSingleton<T>::log;

    class noncopyable
    {
        protected:
            noncopyable (void)
            {
        
            }
        
            ~noncopyable (void)
            {
        
            }
        
        private:
            noncopyable (const noncopyable&);
            const noncopyable& operator= (const noncopyable&);
    };

    //�쳣��
    class CCommException:public std::exception
    {
        public:
            CCommException(const char* fmt...) throw() __attribute ((format(printf, 2, 3)));
            CCommException(int errcode, const char* fmt...) throw()  __attribute ((format(printf, 3, 4)));
            CCommException(const char* errmsg, int errcode = 0) throw():m_errmsg(errmsg), m_errcode(errcode){}
            CCommException(const std::string& errmsg, int errcode = 0) throw():m_errmsg(errmsg), m_errcode(errcode){}
            virtual ~CCommException() throw(){}
        public:
            virtual const char* what() const throw();
            virtual std::string& what_string() throw();
            virtual int ErrorCode(){return m_errcode;};
            virtual void Append(const char* fmt...) throw()  __attribute ((format(printf, 2, 3)));
        protected:
            virtual void AppendMsg(const char* fmt, va_list args) throw();
        protected:
            static const int MAXSIZE = 512;
            std::string m_errmsg;
            int m_errcode;

    };
}
#include "comm_utility.h"
#endif  /* __COMM_BASE_H_8005__ */

