#include <String>
#include <stdexcept>
using namespace std;


	class InvalidSize : public std::runtime_error {

	public:
		InvalidSize(const char* errorMessage);

	};

	class StackFull : public std::runtime_error {

	private:
		int errorVal;

	public:
		StackFull(const char* errorMessage, int errValue);
		int getValue();

	};

	class StackEmpty : public std::runtime_error {

	public:
		StackEmpty(const char* errorMessage);

	};
