
// Strategy pattern example

// select computation inside block, by inheriting a "strategy"

#include <iostream>
using namespace std;

class Operation
{ 
  public:
    Operation() { cout << "+ Operation created" << endl;}
    virtual ~Operation() { cout << "- Operation deleted" << endl;}
    
    void execute(int a, int b)
    {
      cout << "Input: [" << a << "] [" << b << "]" << endl;

      math(a,b);
    }
    
  private:
    virtual void math(int a, int b) = 0;
};

class AddOp: public Operation
{
  public:
    AddOp(): Operation(){}
    
  private:
    void math(int a, int b)
    {
      cout << "Operation: " << "+ (add)" << endl;
      cout << "Result: [" << a + b << "]" << endl;
    }
};

class SubOp: public Operation
{
  public:
    SubOp(): Operation() {}

  private:
    void math(int a, int b)
    {
      cout << "Operation: " << "- (sub)" << endl;
      cout << "Result: [" << a - b << "]" << endl;
    }
};

class MulOp: public Operation
{
  public:
    MulOp(): Operation() {}

  private:
    void math(int a, int b)
    {
      cout << "Operation: " << "* (mul)" << endl;
      cout << "Result: [" << a * b << "]" << endl;
    }
};

class DivOp: public Operation
{
  public:
    DivOp(): Operation() {};
  private:
    void math(int a, int b)
    {
      cout << "Operation: " << "/ (div)" << endl;
      cout << "Result: [" << a / b << "]" << endl;
    }
};

class BlockObject
{
  public:
    enum OperationType{AddOpType, SubOpType, MulOpType, DivOpType};

    BlockObject()
    {
      operation_ = nullptr;
    }
    ~BlockObject()
    {
      delete operation_;
    }

    void set_operation(int optype);
    void calculate(int a, int b);
    
  private:
    Operation* operation_;
};


void BlockObject::set_operation(int type)
{
  delete operation_;

  switch (type)
  {
    case AddOpType: operation_ = new AddOp(); break;
    case SubOpType: operation_ = new SubOp(); break;
    case MulOpType: operation_ = new MulOp(); break;
    case DivOpType: operation_ = new DivOp(); break;
  }

}

void BlockObject::calculate(int a, int b)
{
  operation_->execute(a, b);
}


int main()
{
  enum OperationType{AddOpType, SubOpType, MulOpType, DivOpType};
  BlockObject block;

  block.set_operation(DivOpType);
  block.calculate(810,9);

  block.set_operation(AddOpType);
  block.calculate(810,9);
}