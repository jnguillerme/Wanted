#ifndef  _APP_APP_H_
#define  _APP_APP_H_

class AppData {
	float m_scaleX;
	float m_scaleY;

public:
    /** returns a shared instance of the AppData */
    static AppData sharedData(void) {
    	static AppData theData;
    	return theData;
    };

    AppData();

    const float getScaleX() const 			{ return m_scaleX; }
    void setScaleX(const float scaleX)	{ m_scaleX = scaleX; }

    const float getScaleY() const 			{ return m_scaleY; }
    void setScaleY(const float scaleY)	{ m_scaleY = scaleY; }

};
#endif // _APP_APP_H_
