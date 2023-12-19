//C:\Program Files\Epic Games\UE_5.2\Engine\Source\Runtime\CoreUObject\Public\UObject\PackedObjectRef.h

namespace UE::CoreUObject::Private
{
    /* *
    * FPackedObjectRef表示一个轻量级的引用，可以装入指针空间并能够引用对象
    *(或null)可以加载也可以不加载，而不指向其在内存中的位置(即使它当前已经加载)。
    */
    struct FPackedObjectRef{};
}