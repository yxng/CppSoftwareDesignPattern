#include <iostream>
using namespace std;

// state design pattern 

class System {
	class State* currentState;
public:
	System();

	void SetCurrentState(State* s) { 
		currentState = s;  
	}

	// system state actions
	void GoStandby();
	void GoFault();

};



// abstract base class
class State {
public:
	// functions to be overriden by derived child classes
	virtual void DoStandby(System* sys) {
		cout << "   already Standby\n";
	}

	virtual void DoFault(System* sys) {
		cout << "   already Fault\n";
	}
};

// concrete class header
class Standby : public State{
public:
	Standby()
	{
		cout << "   Standby-ctor ";
	};
	~Standby()
	{
		cout << "   dtor-Standby\n";
	};

	// virtual functions to be overriden by derived child classes
	void DoStandby(System* sys);
	void DoFault(System* sys);

};

class Fault : public State {
public:
	Fault()
	{
		cout << "   Fault-ctor ";
	};
	~Fault()
	{
		cout << "   dtor-Fault\n";
	};

	// pure virtual functions to be overriden by derived child classes
	void DoStandby(System* sys) override;
	void DoFault(System* sys) override;
};


// class member functions 
void Standby::DoStandby(System* s)
{
	cout << "   already Standby";
}

void Standby::DoFault(System* s)
{
	cout << "   going from Standby to Fault";
	s->SetCurrentState(new Fault()); 
	delete this; 
}

// class member functions 
void Fault::DoStandby(System* s)
{
	cout << "   going from Fault to Standby";
	s->SetCurrentState(new Standby());
	delete this;
}

void Fault::DoFault(System* s)
{
	cout << "   already Fault"; 
}


// constructor 
System::System()
{
	currentState = new Fault();
	cout << '\n';
}

void System::GoFault() {
	currentState->DoFault(this);	// passed this System object into state
}

void System::GoStandby() {
	currentState->DoStandby(this);	// passed this System object into state
}

int main() {
	cout << "Software Design Pattern - State Behaviour\n"; 

	System sys; 
	bool isQuit = false; 
	string input; 

	while (!isQuit) {

		// testing keyboard transition 
		cin >> input;

		if (input.compare("x") == 0)
			sys.GoFault();
		else if (input.compare("s") == 0)
			sys.GoStandby();
		else if (input.compare("q") == 0)
			isQuit = true; 
	}

	return 0;
}