#pragma once

class cInterpolator
{
public:
	 cInterpolator();
	~cInterpolator();

	void update( float _delta_time );

	float getProgress( void ) { return m_progress; }
	void  setProgress( float _progress ) { m_progress = _progress; }
	void  setDuration( float _duration ) { m_duration = _duration; }

	/* easing functions */

	float easeIn   ( float _exp );
	float easeInOut( float _exp );
	float easeOut  ( float _exp );

	float easeOutExpo();

private:

	float m_progress = 1.0f;
	float m_duration = 1.0f;

};