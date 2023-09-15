继承类后 可以添加异步内容

```
UCLASS()
class UBlueprintAsyncHttpRequest : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

public:
    // Factory Method
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
        static UBlueprintAsyncHttpRequest* HttpRequest(const FString& URL);

    UPROPERTY(BlueprintAssignable)
        FHttpResponseDelegatge OnSuccess;

    UPROPERTY(BlueprintAssignable)
        FHttpResponseDelegatge OnFail;
};
```

参考资料
https://zhuanlan.zhihu.com/p/107021667