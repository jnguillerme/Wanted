#include "GameCenterMessage.h"

namespace wanted {

bool GameCenterMessage::initWithByteArray(const unsigned int* bytes, const unsigned int size)
{
	if (size == 0) {
		return false;
	}

	m_msgType = bytes[0];
	m_bytes = new unsigned int[size -1];
	memcpy(m_bytes, bytes + 1, (size -1) * sizeof(unsigned int));

	for (int i=0; i < size-1; i++) {
		CCLog("com.jino.wanted.gamecenterMessage - %d >>> [%d][%d]", i, m_bytes[i], bytes[i+1]);
	}
	m_bytesLen = size - 1;
	return true;
}

bool GameCenterMessage::initWithMessageType(const unsigned int msgType)
{
	m_msgType = msgType;
	m_bytes = 0;
	m_bytesLen = 0;
	return true;
}

bool GameCenterMessage::initWithMessageTypeAndParams(const unsigned int msgType, const unsigned int count, va_list args)
{

	m_msgType = msgType;
	m_bytesLen = count;
	m_bytes = new unsigned int[count];

	for (unsigned int i = 0; i < count; i++) {
		m_bytes[i] = va_arg(args, unsigned int);
	}

	for (int i=0; i < m_bytesLen; i++) {
		CCLog("com.jino.wanted.gamecenterMessage - %d >>> [%d]", i, m_bytes[i]);
	}

	return true;

}



} // namespace wanted
