#include<stdio.h>

#ifdef _WIN32
#include <windows.h>
#ifndef NO_EXPORT
#define EXPORT
#endif
#endif

static int a = 1;

/** @brief 印出"t2"
 *  @date 2017/02/28
 *  @author Neo
 *  @param : 如下表:
 *  name     | type     |description of param
 *  ---------|----------|--------------------
 *   argv[0] | char*    | 執行的程式名稱
 *   argv[1] | char*    | 變數1
 *   x       |  x       |   x
 *   x       |  x       |   x
 *   x       |  x       |   x
 *  @return 回傳值說明如下:
 *  name     | type     |description of param
 *  ---------|----------|--------------------
 *   N/A     | void     | 無回傳值
 *  @warning   警告該函數沒有用處
 *  @attention 注意事項沒事不要用這函數
 *  @note      這函數沒有人改過
 *  @todo      不會再改了
 */
void t2(void)
{
  printf("t2\n");
}

/** @brief 負責呼叫t2
 *
 * - 列表項目1
 * - 列表項目2
 * .
 * 列表最後加一個點可以斷行
 * 下一個列表開始前加一個點可以斷行
 * .
 * - 列表項目3
 * - 列表項目4
 * .
 * 列表
 */
void t1(void)
{
  t2();
}


/** @brief 這是主程式
 *  @param argc 表示輸入變數的個數
 *  @param argv 表示輸入變數的矩陣
 *  @return 成功返回0, 失敗返回非0
 */
int main(int argc, char** argv)
{
  /** 可以撰寫多行註解的寫法
      這裡是補充說明的地方
    */
  printf("neo\n");   ///用來撰寫單行註解的寫法, 補充說明的地方
  t1();
  return 0;
}
