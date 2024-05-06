; ModuleID = 'input.cpp'
source_filename = "input.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@passkey = dso_local global i32 0, section "secure_var", align 4
@globalCount = dso_local global i32 9, align 4
@.str = private unnamed_addr constant [19 x i8] c"Function 5 called\0A\00", align 1
@.str.1 = private unnamed_addr constant [19 x i8] c"Function 6 called\0A\00", align 1
@.str.2 = private unnamed_addr constant [19 x i8] c"Function 2 called\0A\00", align 1
@.str.3 = private unnamed_addr constant [19 x i8] c"Function 3 called\0A\00", align 1
@.str.4 = private unnamed_addr constant [19 x i8] c"Function 4 called\0A\00", align 1
@.str.5 = private unnamed_addr constant [19 x i8] c"Function 7 called\0A\00", align 1
@.str.6 = private unnamed_addr constant [35 x i8] c"The Global Function count is : %d\0A\00", align 1
@.str.7 = private unnamed_addr constant [19 x i8] c"Function 8 called\0A\00", align 1
@.str.8 = private unnamed_addr constant [19 x i8] c"Function 1 called\0A\00", align 1
@.str.9 = private unnamed_addr constant [25 x i8] c"Main Function Terminates\00", align 1

; Function Attrs: mustprogress noinline optnone sspstrong uwtable
define dso_local void @_Z9function5v() #0 {
  %1 = call i32 (ptr, ...) @printf(ptr noundef @.str)
  ret void
}

declare i32 @printf(ptr noundef, ...) #1

; Function Attrs: mustprogress noinline optnone sspstrong uwtable
define dso_local void @_Z9function6v() #0 {
  %1 = call i32 (ptr, ...) @printf(ptr noundef @.str.1)
  ret void
}

; Function Attrs: mustprogress noinline optnone sspstrong uwtable
define dso_local void @_Z9function2v() #0 {
  %1 = call i32 (ptr, ...) @printf(ptr noundef @.str.2)
  call void @_Z9function5v()
  ret void
}

; Function Attrs: mustprogress noinline optnone sspstrong uwtable
define dso_local void @_Z9function3v() #0 {
  %1 = call i32 (ptr, ...) @printf(ptr noundef @.str.3)
  call void @_Z9function6v()
  ret void
}

; Function Attrs: mustprogress noinline optnone sspstrong uwtable
define dso_local void @_Z9function4v() #0 {
  %1 = call i32 (ptr, ...) @printf(ptr noundef @.str.4)
  ret void
}

; Function Attrs: mustprogress noinline optnone sspstrong uwtable
define dso_local void @_Z9function7v() #0 {
  %1 = load i32, ptr @passkey, align 4
  %2 = add nsw i32 %1, 1
  store i32 %2, ptr @passkey, align 4
  %3 = call i32 (ptr, ...) @printf(ptr noundef @.str.5)
  ret void
}

; Function Attrs: mustprogress noinline optnone sspstrong uwtable
define dso_local void @_Z9function8v() #0 {
  %1 = load i32, ptr @globalCount, align 4
  %2 = call i32 (ptr, ...) @printf(ptr noundef @.str.6, i32 noundef %1)
  %3 = call i32 (ptr, ...) @printf(ptr noundef @.str.7)
  ret void
}

; Function Attrs: mustprogress noinline optnone sspstrong uwtable
define dso_local void @_Z9function1v() #0 section "secure" {
  %1 = call i32 (ptr, ...) @printf(ptr noundef @.str.8)
  call void @_Z9function2v()
  call void @_Z9function3v()
  call void @_Z9function4v()
  ret void
}

; Function Attrs: mustprogress noinline norecurse optnone sspstrong uwtable
define dso_local noundef i32 @main() #2 {
  %1 = alloca i32, align 4
  store i32 0, ptr %1, align 4
  call void @_Z9function1v()
  call void @_Z9function7v()
  call void @_Z9function8v()
  %2 = call i32 (ptr, ...) @printf(ptr noundef @.str.9)
  ret i32 0
}

attributes #0 = { mustprogress noinline optnone sspstrong uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #2 = { mustprogress noinline norecurse optnone sspstrong uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }

!llvm.module.flags = !{!0, !1, !2, !3, !4}
!llvm.ident = !{!5}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 8, !"PIC Level", i32 2}
!2 = !{i32 7, !"PIE Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 2}
!4 = !{i32 7, !"frame-pointer", i32 2}
!5 = !{!"clang version 16.0.6"}
