#include "cInterpolator.h"

#include <cmath>

cInterpolator::cInterpolator()
{
}

cInterpolator::~cInterpolator()
{
}

void cInterpolator::update( float _delta_time )
{
	m_progress += _delta_time / m_duration;

	if      ( m_progress > 1.0f ) m_progress = 1.0f;
	else if ( m_progress < 0.0f ) m_progress = 0.0f;
}

float cInterpolator::easeIn( float _exp )
{
	return pow( m_progress, _exp );
}

float cInterpolator::easeInOut( float _exp )
{
	return 1 - pow( 1.0f - m_progress, _exp );
}

float cInterpolator::easeOut( float _exp )
{
	if( m_progress < 0.5f )
		return 4 * pow( m_progress, _exp );
	else
		return 1 - pow( -2.0f * m_progress + 2.0f, _exp ) / 2.0f;

}

float cInterpolator::easeOutExpo()
{
	return m_progress == 1.0f ? 1.0f : 1.0f - pow( 2.0f, -10.0f * m_progress );
}
