#include <vcl.h>
#pragma hdrstop

#include "MainOperAuth.h"
//---------------------------------------------------------------------------

int __fastcall Q11ErrorHint(TLabel *LabelHint,String Hint);
bool __fastcall JustNull(TLabeledEdit  *LabeledEdit,TLabel *LabelHint);
bool __fastcall JustDeleteOrNot(String Note,String Msg1,String Msg2);
int __fastcall ErrorHint(TLabel *LabelHint,String Hint);
void __fastcall TileBkground(TImage *Image1);
bool __fastcall JustNumber(TLabeledEdit  *LabeledEdit,TLabel *LabelHint);
bool __fastcall JustLetterAndNumber(TLabeledEdit  *LabeledEdit,TLabel *LabelHint);
bool __fastcall JustLetterAndNumberWithout(TLabeledEdit  *LabeledEdit,TLabel *LabelHint);
bool __fastcall JustLength(int Max,int Min,TLabeledEdit  *LabeledEdit,TLabel *LabelHint);
void __fastcall LoadImageBtn(TImage *Image,int Tag,int Left,int Top,String Text);
int __fastcall GetMaxLenOfStringGridCol(TStringGrid *sg, int nCol);
void __fastcall  SetNodeChecked(TTreeNode *ANode,bool IsSetToChecked);
void __fastcall  CleanNodeChecked(TTreeView *TreeView);
void __fastcall  ShowMenuDetail(AnsiString hint[30]);

int gLID; //=1;        //登陆操作员的标识
String gLCode;// ="admin" ;    //登陆操作员的账号
int gID;           //选中操作员的标识
int gGLMID =101;  // 业务关联菜单标识
AnsiString gGLMTitle ="操作员管理";  // 业务关联菜单标题
const int MAX =25;       // 用于JustLength函数的常量变量
const int MIN =0;         // 用于JustLength函数的常量变量


int __fastcall Q11ErrorHint(TLabel *LabelHint,String Hint)
{
  SplitToStrArray(CallOStr[1],',','T');
  if(strcmp("0",TmpStr[2])==0){
    LabelHint->Caption=Format("%s",ARRAYOFCONST((Hint)));
    return -1;
  }
  else LabelHint->Caption ="查询成功";
  return 0;
}

int __fastcall ErrorHint(TLabel *LabelHint,String Hint)
{
  if(CallOStr[0][0]!='0') {
    LabelHint->Caption=Format("%s,%s",ARRAYOFCONST((CallOStr[1],CallOStr[2])));
    ShowMessage(Format("%s,%s",ARRAYOFCONST((CallOStr[1],CallOStr[2]))));
    return -1;
  }
  else {
    ShowMessage(Hint);
    LabelHint->Caption=Hint;
  }
  return 0;
}


bool __fastcall JustNull(TLabeledEdit  *LabeledEdit,TLabel *LabelHint)
{
  if(LabeledEdit->Text=="") {
    String Hint="不能为空";
    LabelHint->Caption =Format("%s %s",ARRAYOFCONST((LabeledEdit->EditLabel->Caption,Hint)));
    LabeledEdit->SetFocus();
    return true;
  }
  return false;
}

bool __fastcall JustLetterAndNumber(TLabeledEdit  *LabeledEdit,TLabel *LabelHint)
{
  const char *pString =LabeledEdit->Text.c_str();
  if(NULL == pString)  return false;
  while (*pString){
    if (!(*pString >= 'a' && *pString <= 'z' || *pString >= 'A' && *pString <= 'Z' || *pString >= '0' && *pString <= '9'  || *pString=='*')){
      String Hint="只能为数字或者字母或者*";
      LabelHint->Caption =Format("%s %s",ARRAYOFCONST((LabeledEdit->EditLabel->Caption,Hint)));
      LabeledEdit->SetFocus();
      return true;
    }
    pString++;
  }
  return false;
}


bool __fastcall JustLetterAndNumberWithout(TLabeledEdit  *LabeledEdit,TLabel *LabelHint)
{
  const char *pString =LabeledEdit->Text.c_str();
  if(NULL == pString)  return false;
  while (*pString){
    if (!(*pString >= 'a' && *pString <= 'z' || *pString >= 'A' && *pString <= 'Z' || *pString >= '0' && *pString <= '9' )){
      String Hint="只能为数字或者字母";
      LabelHint->Caption =Format("%s %s",ARRAYOFCONST((LabeledEdit->EditLabel->Caption,Hint)));
      LabeledEdit->SetFocus();
      return true;
    }
    pString++;
  }
  return false;
}

bool __fastcall JustLength(int Max,int Min,TLabeledEdit  *LabeledEdit,TLabel *LabelHint)
{
  if( Max < strlen(LabeledEdit->Text.c_str()) || strlen(LabeledEdit->Text.c_str()) < Min ){
    LabelHint->Caption =Format("%s 长度最大为%d,最小为%d ",ARRAYOFCONST((LabeledEdit->EditLabel->Caption,Max,Min)));
    LabeledEdit->SetFocus();
    return true;
  }
  return false;
}


bool __fastcall JustNumber(TLabeledEdit  *LabeledEdit,TLabel *LabelHint)
{
  const char *pString =LabeledEdit->Text.c_str();
  if(NULL == pString)  return false;
  while (*pString){
    if (!(*pString >= '0' && *pString <= '9')){
      String Hint="只能为数字";
      LabelHint->Caption =Format("%s %s",ARRAYOFCONST((LabeledEdit->EditLabel->Caption,Hint)));
      LabeledEdit->SetFocus();
      return true;
    }
    pString++;
  }
  return false;
}

void __fastcall TileBkground(TImage *Image1)
{
  Graphics::TBitmap *bmp;
  bmp = new Graphics::TBitmap();
  bmp->LoadFromFile("D:\\SunRiseRun\\skin\\exeSysM\\exeOper\\bk_client.bmp");
  for(int i=0;i< (Image1->Width+bmp->Width-1)/bmp->Width;i++){
    for(int j=0;j<(Image1->Height+bmp->Height-1)/bmp->Height;j++){
      Image1->Canvas->Draw(i*bmp->Width,j*bmp->Height,bmp);
    }
  }
  delete bmp;
}

void __fastcall LoadImageBtn(TImage *Image,int Tag,int Left,int Top,String Text)
{
  switch(Tag){
    case 1:
      Image->Picture->LoadFromFile("D:\\SunRiseRun\\skin\\exeSysM\\exeOper\\ButtonOper1.bmp");
      break;
    case 2:
      Image->Picture->LoadFromFile("D:\\SunRiseRun\\skin\\exeSysM\\exeOper\\ButtonOper2.bmp");
      break;
    case 3:
      Image->Picture->LoadFromFile("D:\\SunRiseRun\\skin\\exeSysM\\exeOper\\ButtonAdd.bmp");
      break;
    case 4:
      Image->Picture->LoadFromFile("D:\\SunRiseRun\\skin\\exeSysM\\exeOper\\ButtonPage.bmp");
      break;
    case 5:
      Image->Picture->LoadFromFile("D:\\SunRiseRun\\skin\\exeSysM\\exeOper\\ButtonPage2.bmp");
      break;
    case 6:
      Image->Picture->LoadFromFile("D:\\SunRiseRun\\skin\\exeSysM\\exeOper\\ButtonOperClose.bmp");
      break;
    case 7:
      Image->Picture->LoadFromFile("D:\\SunRiseRun\\skin\\exeSysM\\exeOper\\ButtonOperClose2.bmp");
      break;
    default:
      break;
  }
  Image->Canvas->Brush->Style=bsClear ;
  Image->Canvas->TextOutA(Left,Top,Text);
}



bool __fastcall  JustDeleteOrNot(String Note,String Msg1,String Msg2)
{
  String Msg=Format("是否真的删除%s %s %s",ARRAYOFCONST((Note,Msg1,Msg2)));
  if(true==MessageBoxA(NULL,Msg.c_str() ,"确认删除",MB_OKCANCEL))
    return true;
  else
    return false;
}

int __fastcall GetMaxLenOfStringGridCol(TStringGrid *sg, int nCol)
{   // 获取StringGrid中指定列字符串最长的宽度
  int nWidth(0), n;
  String strText;
  for (int i = 0; i < sg->RowCount; i++) {//  i = sg->FixedRows
   strText = sg->Cells[nCol][i];
   n = sg->Canvas->TextWidth(strText);
   if (n > nWidth) nWidth = n;
  }
  return nWidth ; // 这个值可以自己调整
}


void __fastcall  SetNodeChecked(TTreeNode *ANode,bool IsSetToChecked)
{
  TVITEM tvItem;
  tvItem.mask = TVIF_HANDLE | TVIF_STATE;
  tvItem.hItem = ANode->ItemId;
  tvItem.stateMask = TVIS_STATEIMAGEMASK;
  tvItem.state = INDEXTOSTATEIMAGEMASK(IsSetToChecked?2:1);
  TreeView_SetItem(ANode->TreeView->Handle, &tvItem);
}


void __fastcall  CleanNodeChecked(TTreeView *TreeView)
{
  for(int i=0;i<TreeView->Items->Count ;i++){
    SetNodeChecked(TreeView->Items->Item[i],false);
  }
}

void __fastcall  ShowMenuDetail(AnsiString hint[30])
{
  hint[0]="系统管理员唯一能操作的功能界面，可以进行操作员的管理和角色权限管理";
  hint[1]="内部人员测试系统所用到的测试模块";
  hint[2]="引导操作员如何进行手机采集的功能模块";
  hint[3]="进行手机采集的之前不指定关联到案件和嫌疑人";
  hint[4]="可以查看手机采集完成后通讯录短信等等采集结果明细重要信息";
  hint[5]="对案件进行增删改查以及关联等操作";
  hint[6]="案件的增加和编辑";
  hint[7]="可以对案件进行删除操作";
  hint[8]="把嫌疑人关联或者删除到具体的案件";
  hint[9]="把具体案件关联到的嫌疑人的所有采集结果导出";
  hint[10]="登陆操作员能否查询出其余操作员录入的案件";
  hint[11]="对嫌疑人进行增删改查以及物品关联等操作";
  hint[12]="嫌疑人的新增或者资料编辑";
  hint[13]="可以对嫌疑人进行删除操作";
  hint[14]="把嫌疑物品关联或者删除到具体的嫌疑人";
  hint[15]="导出具体嫌疑人采集到的结果";
  hint[16]="对采集具体信息进行关联";
  hint[17]="对未进行案件和嫌疑人管理的采集草稿进行删除";
  hint[18]="可以查看采集到的通讯录具体信息";
  hint[19]="可以查看采集到的通话记录具体信息";
  hint[20]="可以查看采集到的短信息纪录具体信息";
  hint[21]="登陆操作员能否对其余操作员采集的终端信息进行查询";
  hint[22]="引导操作员进行采集操作的助手模块";
  hint[23]="由内部人员使用的功能，新增或者编辑某款手机";
  hint[24]="删除一款手机信息";
  hint[25]="对本系统所有的业务的异动进行查询";
  hint[26]="登陆操作员能否查询其余操作员的业务异动";
  hint[27]="帮助操作员查询手机号码地区、区号地区、特殊号码归属等重要信息";
  hint[28]="根据条件查询出敏感数据";
  hint[29]="查询出采集到的数据";
}
