/******************************************************************************
 * Copyright:      Shenzhen Tecent Co.Ltd.
 *
 * comm_errorcode.h
 *
 * Description:
 *
 * --------------------
 * 2011-6-24, blaketang create
 * --------------------
 ******************************************************************************/
#ifndef __COMM_ERRORCODE_H__062411__
#define __COMM_ERRORCODE_H__062411__

namespace comm
{
//ERROR code��-17000��ͷ�ģ�����14λ����0λ��Ϊ0,���ʾ�˴�������Խ��
//��-16000��ͷ�����14λΪ1, ���ʾ�˴����޷����Խ��
enum EError
{
   EL5Route = -40,   //l5����ʧ��
   ENetwork = -30,   //�������⡢��ʱ

   /*�����Խ���Ĵ���*/
   ERCache = -17000, //cache��ȡʱ����
   EWCache = -17001, //cacheд��ʱ����
   EDiffFlow = -17002,  //���к�
   //EL5Route = -17003,   //l5����ʧ��
   //ENetwork = -17004,   //�������⡢��ʱ

   /*ҵ��*/
   EQQRelation = -17500, //��ϵ��
   EOldVisitor = -17501, //�ɷÿ�
   EProfile = -17502,  //���˵�
   EOidb = -17503,  //oidb
   EComCount = -17504,   //ͳһ����
   ECommentSystem = -17505, //����ϵͳ
   ELike = -17506,      //likeϵͳ
   EDas = -17507,       //DASͳһ�洢

   /*���Բ��ɽ���Ĵ���*/
   EBadParams = -16000,    //��������
   EWupParse = -16001,     //wup/jce��������
   ESystemFailed = -16002, //ϵͳ����
   EInitFailed = -16003,   //��ʼ��ʱʧ��
   EBufSize = -16004,      // bufsize����
   EQzoneIni = -16005,
   EUndefineCmd = -16006,
   EBadData = -16007,      //  �����������ݣ����ܽ�����
   ENoData = -16008,       //  ���ݲ�����
   EProtocolChk = -16009,  //  Э��ͷ���ʧ��
   ERspcode = -16010,      //��������ķ��񷵻��˴���
   EBill = -16011,         //��ˮ����
   EDeny = -16012,         //���ڲ���ԭ�򣬾ܾ�����.
   EBadUin = -16013,       //uin���Ϸ�
   EExceedLimit = -16014,  //�����������ơ���������������Чֵ��Χ
   ENoLogin = -16015,      //û�е�¼
   ENoPermission = -16016,  //û��Ȩ�޲���
   EFrequency = -16017,     //Ƶ������
   EMalicious = -16018,     //����ȫ����Ķ�������
   EDirtyWords = -16020,   //�໰�����д�
   ENotMember = -16021,    //(������)�ǳ�Ա
   ETargetNoMember = -16022, //Ŀ��ǳ�Ա���������߷ǳ�Ա��
   ERepeatData = -16023,      //�ظ�����
};

const int ERETRY_FLAG = 0x1 << 14;
// is able to recover by retrying
//errorcode defined at enum EError
inline bool IsRetryRetcode(int errorcode)
{
   return !(errorcode & (ERETRY_FLAG));
}
}

#endif /* __COMM_ERRORCODE_H__062411__ */
