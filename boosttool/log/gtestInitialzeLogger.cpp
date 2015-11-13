#include <boosttool/log/Logger.hpp>

class InitLogger
{
public:
	InitLogger( void )
	{
		boost::property_tree::ptree tree;
		logger.initialize( "param.ini", tree );
	}

private:
	boosttool::Logger logger;

} logger;

