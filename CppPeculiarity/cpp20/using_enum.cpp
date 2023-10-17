enum class Animal
{
  kCat,
  kGog
};
int main()
{
  Animal animal;
  using enum Animal;
  switch (animal)
  {
  case kCat:
    break;
  }
}
/*
新增支持using enum
*/