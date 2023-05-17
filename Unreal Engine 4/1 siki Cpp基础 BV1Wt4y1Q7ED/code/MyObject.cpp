#include "MyObject.h"
UMyObject::UMyObject() {
	MyFloat = 0.0f;
}
void UMyObject::MyFunction() {
	UE_LOG(LogTemp, Log, TEXT("Hello World"));//输出普通语句
	UE_LOG(LogTemp, Warning, TEXT("Hello World"));//输出黄色语句
	UE_LOG(LogTemp, Error, TEXT("Hello World"));//输出红色语句
}