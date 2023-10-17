#include <iostream>
#include <exception>
using namespace std;
class AClass{
  virtual void dummy() {}
};
class BClass : public AClass{
public:
  int a;
};
int main(){
  try  {
    AClass *abc = new BClass;
    AClass *aac = new AClass;
    BClass *bc;
    bc = dynamic_cast<BClass *>(abc);
    if (bc == nullptr)
      cout << "1" << endl;
    // null
    bc = dynamic_cast<BClass *>(aac); // will null
    if (bc == nullptr)
      cout << "2" << endl;
    // 2
  }
  catch (exception &e)
  {
    cout << "Exception: " << e.what();
  }
  return 0;
}
