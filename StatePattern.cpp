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
	void GoSeedOn();

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

	virtual void DoSeedOn(System* sys) {
		cout << "   already Seedon\n";
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

	// pure virtual functions to be overriden by derived child classes
	void DoStandby(System* sys);
	void DoFault(System* sys);
	void DoSeedOn(System* sys);
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
	void DoSeedOn(System* sys) override;
};

class SeedOn : public State {
public:
	SeedOn()
	{
		cout << "   SeedOn-ctor ";
	};
	~SeedOn()
	{
		cout << "   dtor-SeedOn\n";
	};

	// pure virtual functions to be overriden by derived child classes
	void DoStandby(System* sys) override;
	void DoFault(System* sys) override;
	void DoSeedOn(System* sys) override;
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

void Standby::DoSeedOn(System* s)
{
	cout << "   going from Standby to SeedOn";
	s->SetCurrentState(new SeedOn());
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

void Fault::DoSeedOn(System* s)
{
	cout << "   Not allowed";
}

// class member functions 
void SeedOn::DoStandby(System* s)
{
	cout << "   going from SeedOn to Standby";
	s->SetCurrentState(new Standby());
	delete this;
}

void SeedOn::DoFault(System* s)
{
	cout << "   Not allowed";
}

void SeedOn::DoSeedOn(System* s)
{
	cout << "   already SeedOn";  
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

void System::GoSeedOn() {
	currentState->DoSeedOn(this);	// passed this System object into state
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
		else if (input.compare("f") == 0)
			sys.GoSeedOn();
		else if (input.compare("q") == 0)
			isQuit = true; 
	}

	return 0;
}