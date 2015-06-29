#ifndef _LIBAUDPOSTPROCESS_H_
#define _LIBAUDPOSTPROCESS_H_

#if defined(_MSC_VER)
#include <windows.h>
#define LINKING WINAPI
#else
#define LINKING
#endif

#ifdef __cplusplus
extern "C"
{
#endif

/*********** ��Ч���ID ***********/
#define COMPONENT_ID_VOCAL_FIX      0x1001	/* ������Ƶ�޸��ͽ��� */
#define COMPONENT_ID_VOCAL_HARMONIC 0x1002	/* ����г�����������Ⱥ�ů�� */
#define COMPONENT_ID_VOCAL_AGC      0x1003	/* ����A/C�������� */
#define COMPONENT_ID_VOCAL_REVERB   0x1004	/* �������� */
#define COMPONENT_ID_BG_AGC         0x2001	/* ����A/C�������� */
#define COMPONENT_ID_BG_SURROUND    0x2002	/* ����3D���� */
#define COMPONENT_ID_BG_REVERB      0x2003	/* ������� */
/**********************************/

// ����Ԥ������ID(EAX��׼)
// HQ���ȫ��ʹ�ã�LQ�水�·�ע��Ϊ׼
static const int REVERB_PRESET_ID[113] =
{
	0,		// һ��(Ĭ��)��LQ�����
	1,		// ����Ϊ����С����
	2,		// KTV���䣬LQ�����
	3,		// ԡ�ң�LQ�����
	4,		// �����
	5,		// ʯͷ��
	6,		// �����ã�LQ�����
	7,		// ��������LQ�����
	8,		// ɽ��
	9,		// ����̨/������
	10,		// �ɻ���
	11,		// �̵�̺������
	12,		// һ������
	13,		// ʯ������
	14,		// ��ͬ/С����
	15,		// ɭ��
	16,		// ���й㳡
	17,		// ɽ��֮��(Ⱥɽ��)
	18,		// ��
	19,		// ������ƽ��
	20,		// ͣ����
	21,		// ����ˮ�ܵ�
	22,		// ˮ��
	23,		// �����״̬
	24,		// ѣ��״̬
	25,		// ���״̬
	26,		// �Ǳ���С����
	27,		// �Ǳ�����ͨ��
	28,		// �Ǳ����еȷ���
	29,		// �Ǳ����󷿼�
	30,		// �Ǳ�����ͨ��
	31,		// �Ǳ�������
	32,		// �Ǳ�������
	33,		// �Ǳ���ͥԺ
	34,		// �Ǳ���Сͤ��
	35,		// ������С����
	36,		// ��������ͨ��
	37,		// �������еȷ���
	38,		// �������󷿼�
	39,		// ��������ͨ��
	40,		// ����������
	41,		// ����������
	42,		// ��������Ժ
	43,		// ������Сͤ��
	44,		// ������С����
	45,		// ��������ͨ��
	46,		// �������еȷ���
	47,		// �������󷿼�
	48,		// ��������ͨ��
	49,		// ����������
	50,		// ����������
	51,		// ��������԰
	52,		// ������Сͤ��
	53,		// �ռ�վ��С����
	54,		// �ռ�վ����ͨ��
	55,		// �ռ�վ���еȷ���
	56,		// �ռ�վ���󷿼�
	57,		// �ռ�վ����ͨ��
	58,		// �ռ�վ��������
	59,		// �ռ�վ������
	60,		// �ռ�վ��ֲ��԰
	61,		// ľ�ݣ�С����
	62,		// ľ�ݣ���ͨ��
	63,		// ľ�ݣ��еȷ���
	64,		// ľ�ݣ��󷿼�
	65,		// ľ�ݣ���ͨ��
	66,		// ľ�ݣ�����
	67,		// ľ�ݣ�����
	68,		// ľ�ݣ�����
	69,		// ľ�ݣ�ֲ��԰
	70,		// ������/�ݣ��յ�������
	71,		// ������/�ݣ�����
	72,		// ������/�ݣ�С��Ӿ��
	73,		// ������/�ݣ�����Ӿ��
	74,		// ������/�ݣ�����
	75,		// ������/�ݣ���������
	76,		// ������/�ݣ���������������
	77,		// ������
	78,		// ѧУ����ݽ���
	79,		// ��ϰ��
	80,		// С�ͷ���
	81,		// ���ͷ���
	82,		// ����Բ����
	83,		// С�ܵ�
	84,		// Բ��ʥ����
	85,		// ϸ���ܵ�
	86,		// ��ܵ�
	87,		// �ᷢ������Ĺܵ�
	88,		// ��԰
	89,		// �����ƽԭ
	90,		// �����Ͽ��
	91,		// СϪ
	92,		// ɽ��
	93,		// ���飬��졢ƽ��
	94,		// ���飬���ص�
	95,		// ���飬������
	96,		// ��ʻ/���������ۡ��԰�
	97,		// ��ʻ/������ͣ����
	98,		// ��ʻ/����������
	99,		// ��ʻ/�������˶����ܳ�������
	100,	// ��ʻ/�����������ݻ���
	101,	// ��ʻ/�����������Ŀ�̨
	102,	// ��ʻ/�������յĿ�̨
	103,	// ��ʻ/���������
	104,	// ���У��ֵ���
	105,	// ���У�����
	106,	// ���У������
	107,	// ���У�ͼ���
	108,	// ���У�����ͨ��
	109,	// ���У�����������
	110,	// �����ҳ��ķ���
	111,	// ���ã������
	112		// Сˮ��
};

/************* ��Ч��API *************/
// ��Ч���Ĳ���������ĵ���

// ����һ����Ч��ʵ��
// �������NULL�ɹ���NULLʧ��(�ڴ治��)
void* LINKING CreateVAPInstance();

// �ͷ�һ����Ч��ʵ��
// �����������Ч��ʵ��
void LINKING FreeVAPInstance(void *pInstance);

// �趨PCM���ݵĲ�����
// ���������nSamplingRate[������Hz]��pInstance[��Ч��ʵ��]
// �����0�ɹ���-1�����ʲ�֧��
int LINKING SetSamplingRate(int nSamplingRate, void *pInstance);

// �趨PCM���ݵ�������
// ���������nChannels[ͨ������]��pInstance[��Ч��ʵ��]
// �����0�ɹ���-1�����ʲ�֧��
int LINKING SetChannels(int nChannels, void *pInstance);

// �趨��Ч����Ŀ�����رգ�Ĭ�Ϲر��������
// ���������nID[��Ч�����ID]��bEnabled[�Ƿ����ã�0�رգ�1����]��pInstance[��Ч��ʵ��]
void LINKING EnableComponent(int nID, int bEnabled, void *pInstance);

// �趨�����A/C�����������
// ���������rRatio[���Ʊ��ʣ�1.0~5.0]��rVolume[���������0~1.0]��rMaxGain[���Ŵ�����1.0~32.0]��pInstance[��Ч��ʵ��]
void LINKING SetBGAGCParameters(float rRatio, float rVolume, float rMaxGain, void *pInstance);

// �趨�����3D����ǿ��
// ���������rStereoWeight[���ƶȣ�1.0~2.5]��rImageWeight[����ǿ�ȣ�1.0~2.5]��pInstance[��Ч��ʵ��]
void LINKING SetBGSurParameters(float rStereoWeight, float rImageWeight, void *pInstance);

// �趨����Ļ������
// ���������nPresetID[����Ԥ������ID]��rDry[���źţ�0~2.0]��rWet[ʪ�źţ�0~2.0]��pInstance[��Ч��ʵ��]
void LINKING SetBGReverbPreset(const int nPresetID, float rDry, float rWet, void *pInstance);

// �趨�����ĸ�Ƶ�����ͽ������
// ���������nBandFreqLimit[��Ƶ���ƺͽ������Hz��2000~18000]��pInstance[��Ч��ʵ��]
void LINKING SetVocalFixParameters(int nBandFreqLimit, void *pInstance);

// �趨������г������LQ�治֧��
// ���������fvHarMag[����г���ķ���]��pInstance[��Ч��ʵ��]
void LINKING SetVocalHarmonicParameters(float fvHarMag[10], void *pInstance);

// �趨������A/C�����������
// ���������rRatio[���Ʊ��ʣ�1.0~5.0]��rVolume[���������0~1.0]��rMaxGain[���Ŵ�����1.0~32.0]��pInstance[��Ч��ʵ��]
void LINKING SetVocalAGCParameters(float rRatio, float rVolume, float rMaxGain, void *pInstance);

// �趨�����Ļ������
// ���������nPresetID[����Ԥ������ID]��rDry[���źţ�0~2.0]��rWet[ʪ�źţ�0~2.0]��pInstance[��Ч��ʵ��]
void LINKING SetVocalReverbPreset(const int nPresetID, float rDry, float rWet, void *pInstance);

// ����һ�������Ԥ�����õ����������
// ���������nPresetID[����Ԥ������ID]��pInstance[��Ч��ʵ��]
void LINKING LoadPreset(const int nPresetID, void *pInstance);

// ��λЧ����
// ���������pInstance[��Ч��ʵ��]
void LINKING Reset(void *pInstance);

// �������Buffer��16λ����PCM��ʽ
// ���������s16Buffer[PCM���ݵ�ַ]��nFrameCount[PCM����֡��]��pInstance[��Ч��ʵ��]
// ��������������s16Buffer����������PCM����֡��
int LINKING ProcessBackground_s16(short *s16Buffer, int nFrameCount, void *pInstance);

// �������Buffer��32λ����PCM��ʽ��LQ�治֧��
// ���������f32Buffer[PCM���ݵ�ַ]��nFrameCount[PCM����֡��]��pInstance[��Ч��ʵ��]
// ��������������f32Buffer����������PCM����֡��
int LINKING ProcessBackground_f32(float *f32Buffer, int nFrameCount, void *pInstance);

// ��������Buffer��16λ����PCM��ʽ
// ���������s16Buffer[PCM���ݵ�ַ]��nFrameCount[PCM����֡��]��pInstance[��Ч��ʵ��]
// ��������������s16Buffer����������PCM����֡��
int LINKING ProcessVocal_s16(short *s16Buffer, int nFrameCount, void *pInstance);

// ��������Buffer��32λ����PCM��ʽ��LQ�治֧��
// ���������f32Buffer[PCM���ݵ�ַ]��nFrameCount[PCM����֡��]��pInstance[��Ч��ʵ��]
// ��������������f32Buffer����������PCM����֡��
int LINKING ProcessVocal_f32(float *f32Buffer, int nFrameCount, void *pInstance);
/*************************************/

#ifdef __cplusplus
}
#endif

#endif
