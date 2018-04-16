
// class for data types

#include <vector>
#include <iostream>
#include <map>

class DataType
{
  protected:
    std::map<std::string, double> data;
};

class simple: public DataType
{
    public:
        simple()
        {
            this->data.insert(std::pair <std::string, double> ("val", 0.0));
        }

        setValue(double value)
        {
            this->data["val"] = value;
        }

        print()
        {
            std::cout << "val = " << this->data["val"] << std::endl;
        }

};

class point3d: public DataType
{
    public:
        point3d()
        {
            this->data.insert(std::pair <std::string, double> ("x", 0.0));
            this->data.insert(std::pair <std::string, double> ("y", 0.0));
            this->data.insert(std::pair <std::string, double> ("z", 0.0));
        }

        setValue(double x_value, double y_value, double z_value)
        {
            this->data["x"] = x_value;
            this->data["y"] = y_value;
            this->data["z"] = z_value;
        }

        print()
        {
            std::cout << "x = " << this->data["x"] << " | y = " << this->data["y"] << " | z = " << this->data["z"] << std::endl;
        }

};

int main()
{
  simple drat;
  drat.print();
  drat.setValue(1.25);
  drat.print();

  point3d bodVprostoru;
  bodVprostoru.print();
  bodVprostoru.setValue(5.0, 8.1, 3.64);
  bodVprostoru.print();
}