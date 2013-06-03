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

int gLID; //=1;        //��½����Ա�ı�ʶ
String gLCode;// ="admin" ;    //��½����Ա���˺�
int gID;           //ѡ�в���Ա�ı�ʶ
int gGLMID =101;  // ҵ������˵���ʶ
AnsiString gGLMTitle ="����Ա����";  // ҵ������˵�����
const int MAX =25;       // ����JustLength�����ĳ�������
const int MIN =0;         // ����JustLength�����ĳ�������


int __fastcall Q11ErrorHint(TLabel *LabelHint,String Hint)
{
  SplitToStrArray(CallOStr[1],',','T');
  if(strcmp("0",TmpStr[2])==0){
    LabelHint->Caption=Format("%s",ARRAYOFCONST((Hint)));
    return -1;
  }
  else LabelHint->Caption ="��ѯ�ɹ�";
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
    String Hint="����Ϊ��";
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
      String Hint="ֻ��Ϊ���ֻ�����ĸ����*";
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
      String Hint="ֻ��Ϊ���ֻ�����ĸ";
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
    LabelHint->Caption =Format("%s �������Ϊ%d,��СΪ%d ",ARRAYOFCONST((LabeledEdit->EditLabel->Caption,Max,Min)));
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
      String Hint="ֻ��Ϊ����";
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
  String Msg=Format("�Ƿ����ɾ��%s %s %s",ARRAYOFCONST((Note,Msg1,Msg2)));
  if(true==MessageBoxA(NULL,Msg.c_str() ,"ȷ��ɾ��",MB_OKCANCEL))
    return true;
  else
    return false;
}

int __fastcall GetMaxLenOfStringGridCol(TStringGrid *sg, int nCol)
{   // ��ȡStringGrid��ָ�����ַ�����Ŀ��
  int nWidth(0), n;
  String strText;
  for (int i = 0; i < sg->RowCount; i++) {//  i = sg->FixedRows
   strText = sg->Cells[nCol][i];
   n = sg->Canvas->TextWidth(strText);
   if (n > nWidth) nWidth = n;
  }
  return nWidth ; // ���ֵ�����Լ�����
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
  hint[0]="ϵͳ����ԱΨһ�ܲ����Ĺ��ܽ��棬���Խ��в���Ա�Ĺ���ͽ�ɫȨ�޹���";
  hint[1]="�ڲ���Ա����ϵͳ���õ��Ĳ���ģ��";
  hint[2]="��������Ա��ν����ֻ��ɼ��Ĺ���ģ��";
  hint[3]="�����ֻ��ɼ���֮ǰ��ָ��������������������";
  hint[4]="���Բ鿴�ֻ��ɼ���ɺ�ͨѶ¼���ŵȵȲɼ������ϸ��Ҫ��Ϣ";
  hint[5]="�԰���������ɾ�Ĳ��Լ������Ȳ���";
  hint[6]="���������Ӻͱ༭";
  hint[7]="���Զ԰�������ɾ������";
  hint[8]="�������˹�������ɾ��������İ���";
  hint[9]="�Ѿ��尸���������������˵����вɼ��������";
  hint[10]="��½����Ա�ܷ��ѯ���������Ա¼��İ���";
  hint[11]="�������˽�����ɾ�Ĳ��Լ���Ʒ�����Ȳ���";
  hint[12]="�����˵������������ϱ༭";
  hint[13]="���Զ������˽���ɾ������";
  hint[14]="��������Ʒ��������ɾ���������������";
  hint[15]="�������������˲ɼ����Ľ��";
  hint[16]="�Բɼ�������Ϣ���й���";
  hint[17]="��δ���а����������˹���Ĳɼ��ݸ����ɾ��";
  hint[18]="���Բ鿴�ɼ�����ͨѶ¼������Ϣ";
  hint[19]="���Բ鿴�ɼ�����ͨ����¼������Ϣ";
  hint[20]="���Բ鿴�ɼ����Ķ���Ϣ��¼������Ϣ";
  hint[21]="��½����Ա�ܷ���������Ա�ɼ����ն���Ϣ���в�ѯ";
  hint[22]="��������Ա���вɼ�����������ģ��";
  hint[23]="���ڲ���Աʹ�õĹ��ܣ��������߱༭ĳ���ֻ�";
  hint[24]="ɾ��һ���ֻ���Ϣ";
  hint[25]="�Ա�ϵͳ���е�ҵ����춯���в�ѯ";
  hint[26]="��½����Ա�ܷ��ѯ�������Ա��ҵ���춯";
  hint[27]="��������Ա��ѯ�ֻ�������������ŵ�������������������Ҫ��Ϣ";
  hint[28]="����������ѯ����������";
  hint[29]="��ѯ���ɼ���������";
}
