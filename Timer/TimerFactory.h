class CTimerImplementation;

class CTimerFactory
{
public:
	static void	RegisterFactory();

	virtual CTimerImplementation*	CreatePlatform() const = 0;
};
