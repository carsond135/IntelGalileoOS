/*
 * EfiVfrParser: P a r s e r  H e a d e r 
 *
 * Generated from: VfrSyntax.g
 *
 * Terence Parr, Russell Quong, Will Cohen, and Hank Dietz: 1989-2001
 * Parr Research Corporation
 * with Purdue University Electrical Engineering
 * with AHPCRC, University of Minnesota
 * ANTLR Version 1.33MR33
 */

#ifndef EfiVfrParser_h
#define EfiVfrParser_h

#ifndef ANTLR_VERSION
#define ANTLR_VERSION 13333
#endif

#include "AParser.h"



#include "EfiVfr.h"
#include "VfrFormPkg.h"
#include "VfrError.h"
#include "VfrUtilityLib.h"
#include "AToken.h"
#include "ATokPtr.h"
class EfiVfrParser : public ANTLRParser {
public:
	static  const ANTLRChar *tokenName(int tk);
	enum { SET_SIZE = 253 };
protected:
	static const ANTLRChar *_token_tbl[];
private:
protected:
	static SetWordType err1[32];
	static SetWordType err2[32];
	static SetWordType err3[32];
	static SetWordType err4[32];
	static SetWordType setwd1[253];
	static SetWordType err5[32];
	static SetWordType err6[32];
	static SetWordType err7[32];
	static SetWordType err8[32];
	static SetWordType err9[32];
	static SetWordType err10[32];
	static SetWordType err11[32];
	static SetWordType setwd2[253];
	static SetWordType err12[32];
	static SetWordType err13[32];
	static SetWordType err14[32];
	static SetWordType err15[32];
	static SetWordType err16[32];
	static SetWordType err17[32];
	static SetWordType err18[32];
	static SetWordType err19[32];
	static SetWordType err20[32];
	static SetWordType setwd3[253];
	static SetWordType err21[32];
	static SetWordType err22[32];
	static SetWordType err23[32];
	static SetWordType err24[32];
	static SetWordType err25[32];
	static SetWordType err26[32];
	static SetWordType err27[32];
	static SetWordType setwd4[253];
	static SetWordType err28[32];
	static SetWordType err29[32];
	static SetWordType err30[32];
	static SetWordType err31[32];
	static SetWordType err32[32];
	static SetWordType setwd5[253];
	static SetWordType err33[32];
	static SetWordType err34[32];
	static SetWordType err35[32];
	static SetWordType err36[32];
	static SetWordType err37[32];
	static SetWordType err38[32];
	static SetWordType err39[32];
	static SetWordType err40[32];
	static SetWordType err41[32];
	static SetWordType err42[32];
	static SetWordType setwd6[253];
	static SetWordType err43[32];
	static SetWordType err44[32];
	static SetWordType err45[32];
	static SetWordType err46[32];
	static SetWordType err47[32];
	static SetWordType err48[32];
	static SetWordType err49[32];
	static SetWordType err50[32];
	static SetWordType err51[32];
	static SetWordType err52[32];
	static SetWordType err53[32];
	static SetWordType setwd7[253];
	static SetWordType err54[32];
	static SetWordType err55[32];
	static SetWordType err56[32];
	static SetWordType setwd8[253];
	static SetWordType err57[32];
	static SetWordType err58[32];
	static SetWordType err59[32];
	static SetWordType err60[32];
	static SetWordType err61[32];
	static SetWordType err62[32];
	static SetWordType err63[32];
	static SetWordType setwd9[253];
	static SetWordType err64[32];
	static SetWordType err65[32];
	static SetWordType err66[32];
	static SetWordType err67[32];
	static SetWordType err68[32];
	static SetWordType setwd10[253];
	static SetWordType err69[32];
	static SetWordType setwd11[253];
	static SetWordType err70[32];
	static SetWordType err71[32];
	static SetWordType err72[32];
	static SetWordType err73[32];
	static SetWordType setwd12[253];
	static SetWordType err74[32];
	static SetWordType err75[32];
	static SetWordType err76[32];
	static SetWordType err77[32];
	static SetWordType setwd13[253];
	static SetWordType err78[32];
	static SetWordType err79[32];
	static SetWordType err80[32];
	static SetWordType err81[32];
	static SetWordType err82[32];
	static SetWordType setwd14[253];
	static SetWordType err83[32];
	static SetWordType err84[32];
	static SetWordType err85[32];
	static SetWordType setwd15[253];
	static SetWordType err86[32];
	static SetWordType err87[32];
	static SetWordType err88[32];
	static SetWordType err89[32];
	static SetWordType err90[32];
	static SetWordType err91[32];
	static SetWordType err92[32];
	static SetWordType err93[32];
	static SetWordType err94[32];
	static SetWordType setwd16[253];
	static SetWordType err95[32];
	static SetWordType err96[32];
	static SetWordType err97[32];
	static SetWordType err98[32];
	static SetWordType err99[32];
	static SetWordType err100[32];
	static SetWordType err101[32];
	static SetWordType setwd17[253];
	static SetWordType err102[32];
	static SetWordType err103[32];
	static SetWordType err104[32];
	static SetWordType err105[32];
	static SetWordType setwd18[253];
	static SetWordType err106[32];
	static SetWordType err107[32];
	static SetWordType err108[32];
	static SetWordType setwd19[253];
	static SetWordType err109[32];
	static SetWordType err110[32];
	static SetWordType err111[32];
	static SetWordType err112[32];
	static SetWordType err113[32];
	static SetWordType err114[32];
	static SetWordType err115[32];
	static SetWordType setwd20[253];
	static SetWordType err116[32];
	static SetWordType err117[32];
	static SetWordType err118[32];
	static SetWordType err119[32];
	static SetWordType setwd21[253];
	static SetWordType err120[32];
	static SetWordType err121[32];
	static SetWordType err122[32];
	static SetWordType err123[32];
	static SetWordType err124[32];
	static SetWordType setwd22[253];
	static SetWordType err125[32];
	static SetWordType err126[32];
	static SetWordType err127[32];
	static SetWordType err128[32];
	static SetWordType err129[32];
	static SetWordType setwd23[253];
	static SetWordType err130[32];
	static SetWordType err131[32];
	static SetWordType err132[32];
	static SetWordType err133[32];
	static SetWordType setwd24[253];
	static SetWordType err134[32];
	static SetWordType err135[32];
	static SetWordType err136[32];
	static SetWordType err137[32];
	static SetWordType err138[32];
	static SetWordType err139[32];
	static SetWordType setwd25[253];
	static SetWordType err140[32];
	static SetWordType setwd26[253];
	static SetWordType err141[32];
	static SetWordType err142[32];
	static SetWordType setwd27[253];
	static SetWordType err143[32];
	static SetWordType err144[32];
	static SetWordType err145[32];
	static SetWordType setwd28[253];
	static SetWordType err146[32];
	static SetWordType err147[32];
	static SetWordType err148[32];
	static SetWordType setwd29[253];
	static SetWordType err149[32];
	static SetWordType err150[32];
	static SetWordType err151[32];
	static SetWordType setwd30[253];
	static SetWordType err152[32];
	static SetWordType setwd31[253];
	static SetWordType err153[32];
	static SetWordType err154[32];
	static SetWordType setwd32[253];
	static SetWordType err155[32];
	static SetWordType err156[32];
	static SetWordType err157[32];
	static SetWordType err158[32];
	static SetWordType setwd33[253];
	static SetWordType err159[32];
	static SetWordType err160[32];
	static SetWordType err161[32];
	static SetWordType err162[32];
	static SetWordType err163[32];
	static SetWordType err164[32];
	static SetWordType setwd34[253];
	static SetWordType err165[32];
	static SetWordType err166[32];
	static SetWordType err167[32];
	static SetWordType err168[32];
	static SetWordType setwd35[253];
	static SetWordType setwd36[253];
	static SetWordType err169[32];
	static SetWordType setwd37[253];
	static SetWordType err170[32];
	static SetWordType err171[32];
	static SetWordType err172[32];
	static SetWordType err173[32];
	static SetWordType setwd38[253];
	static SetWordType err174[32];
	static SetWordType err175[32];
	static SetWordType err176[32];
	static SetWordType err177[32];
	static SetWordType setwd39[253];
	static SetWordType err178[32];
	static SetWordType err179[32];
	static SetWordType err180[32];
	static SetWordType err181[32];
	static SetWordType err182[32];
	static SetWordType setwd40[253];
	static SetWordType err183[32];
	static SetWordType err184[32];
	static SetWordType err185[32];
	static SetWordType setwd41[253];
	static SetWordType err186[32];
	static SetWordType setwd42[253];
	static SetWordType err187[32];
	static SetWordType setwd43[253];
private:
	void zzdflthandlers( int _signal, int *_retsignal );

public:
	EfiVfrParser(ANTLRTokenBuffer *input);
	UINT8 vfrProgram(void);
	void pragmaPackShowDef(void);
	void pragmaPackStackDef(void);
	void pragmaPackNumber(void);
	void vfrPragmaPackDefinition(void);
	void vfrDataStructDefinition(void);
	void vfrDataStructFields(void);
	void dataStructField64(void);
	void dataStructField32(void);
	void dataStructField16(void);
	void dataStructField8(void);
	void dataStructFieldBool(void);
	void dataStructFieldString(void);
	void dataStructFieldDate(void);
	void dataStructFieldTime(void);
	void dataStructFieldRef(void);
	void dataStructFieldUser(void);
	void guidSubDefinition(EFI_GUID & Guid);
	void guidDefinition(EFI_GUID & Guid);
	void vfrFormSetDefinition(void);
	void vfrFormSetList(void);
	void vfrStatementExtension(void);
	void vfrExtensionData(UINT8 * DataBuff,UINT32 Size,CHAR8 * TypeName,UINT32 TypeSize,BOOLEAN IsStruct,UINT32 ArrayNum);
	void vfrStatementDefaultStore(void);
	void vfrStatementVarStoreLinear(void);
	void vfrStatementVarStoreEfi(void);
	void vfrVarStoreEfiAttr(UINT32 & Attr);
	void vfrStatementVarStoreNameValue(void);
	void classDefinition(UINT16 & Class);
	void validClassNames(UINT16 & Class);
	void subclassDefinition(UINT16 & SubClass);
	void vfrStatementDisableIfFormSet(void);
	void vfrStatementSuppressIfFormSet(void);
	void vfrStatementHeader(CIfrStatementHeader * SHObj);
	void vfrQuestionHeader(CIfrQuestionHeader & QHObj,EFI_QUESION_TYPE QType = QUESTION_NORMAL);
	void questionheaderFlagsField(UINT8 & Flags);
	void vfrStorageVarId(EFI_VARSTORE_INFO & Info,CHAR8 *& QuestVarIdStr,BOOLEAN CheckFlag = TRUE);
	void vfrQuestionDataFieldName(EFI_QUESTION_ID & QId,UINT32 & Mask,CHAR8 *& VarIdStr,UINT32 & LineNo);
	EFI_IFR_TYPE_VALUE vfrConstantValueField(UINT8 Type);
	void vfrFormDefinition(void);
	void vfrFormMapDefinition(void);
	void vfrStatementRules(void);
	void vfrStatementDefault(void);
	void vfrStatementStat(void);
	void vfrStatementQuestions(void);
	void vfrStatementConditional(void);
	void vfrStatementConditionalNew(void);
	void vfrStatementSuppressIfStat(void);
	void vfrStatementGrayOutIfStat(void);
	void vfrStatementInvalid(void);
	void flagsField(void);
	void vfrStatementValue(void);
	void vfrStatementRead(void);
	void vfrStatementWrite(void);
	void vfrStatementSubTitle(void);
	void vfrSubtitleFlags(CIfrSubtitle & SObj);
	void subtitleFlagsField(UINT8 & Flags);
	void vfrStatementStaticText(void);
	void staticTextFlagsField(UINT8 & HFlags);
	void vfrStatementCrossReference(void);
	void vfrStatementGoto(void);
	void vfrGotoFlags(CIfrQuestionHeader * QHObj,UINT32 LineNum);
	void gotoFlagsField(UINT8 & HFlags);
	void getStringId(void);
	void vfrStatementResetButton(void);
	void vfrStatementBooleanType(void);
	void vfrStatementCheckBox(void);
	void vfrCheckBoxFlags(CIfrCheckBox & CBObj,UINT32 LineNum);
	void checkboxFlagsField(UINT8 & LFlags,UINT8 & HFlags);
	void vfrStatementAction(void);
	void vfrActionFlags(CIfrAction & AObj,UINT32 LineNum);
	void actionFlagsField(UINT8 & HFlags);
	void vfrStatementDate(void);
	void minMaxDateStepDefault(EFI_HII_DATE & D,UINT8 KeyValue);
	void vfrDateFlags(CIfrDate & DObj,UINT32 LineNum);
	void dateFlagsField(UINT8 & Flags);
	void vfrStatementNumericType(void);
	void vfrSetMinMaxStep(CIfrMinMaxStepData & MMSDObj);
	void vfrStatementNumeric(void);
	void vfrNumericFlags(CIfrNumeric & NObj,UINT32 LineNum);
	void numericFlagsField(UINT8 & HFlags,UINT8 & LFlags);
	void vfrStatementOneOf(void);
	void vfrOneofFlagsField(CIfrOneOf & OObj,UINT32 LineNum);
	void vfrStatementStringType(void);
	void vfrStatementString(void);
	void vfrStringFlagsField(CIfrString & SObj,UINT32 LineNum);
	void stringFlagsField(UINT8 & HFlags,UINT8 & LFlags);
	void vfrStatementPassword(void);
	void vfrPasswordFlagsField(CIfrPassword & PObj,UINT32 LineNum);
	void passwordFlagsField(UINT8 & HFlags);
	void vfrStatementOrderedList(void);
	void vfrOrderedListFlags(CIfrOrderedList & OLObj,UINT32 LineNum);
	void orderedlistFlagsField(UINT8 & HFlags,UINT8 & LFlags);
	void vfrStatementTime(void);
	void minMaxTimeStepDefault(EFI_HII_TIME & T,UINT8 KeyValue);
	void vfrTimeFlags(CIfrTime & TObj,UINT32 LineNum);
	void timeFlagsField(UINT8 & Flags);
	void vfrStatementQuestionTag(void);
	void vfrStatementQuestionTagList(void);
	void vfrStatementQuestionOptionTag(void);
	void vfrStatementQuestionOptionList(void);
	void vfrStatementStatList(void);
	void vfrStatementStatListOld(void);
	void vfrStatementDisableIfStat(void);
	void vfrStatementInconsistentIfStat(void);
	void vfrStatementgrayoutIfSuppressIf(void);
	void vfrStatementsuppressIfGrayOutIf(void);
	void vfrStatementSuppressIfStatNew(void);
	void vfrStatementGrayOutIfStatNew(void);
	void vfrStatementSuppressIfStatOld(void);
	void vfrStatementGrayOutIfStatOld(void);
	void vfrImageTag(void);
	void vfrLockedTag(void);
	void vfrModalTag(void);
	void vfrStatementStatTag(void);
	void vfrStatementStatTagList(void);
	void vfrStatementImage(void);
	void vfrStatementModal(void);
	void vfrStatementLocked(void);
	void vfrStatementInconsistentIf(void);
	void vfrStatementNoSubmitIf(void);
	void vfrStatementDisableIfQuest(void);
	void vfrStatementRefresh(void);
	void vfrStatementRefreshEvent(void);
	void vfrStatementVarstoreDevice(void);
	void vfrStatementSuppressIfQuest(void);
	void vfrStatementGrayOutIfQuest(void);
	void vfrStatementOptions(void);
	void vfrStatementOneOfOption(void);
	void vfrOneOfOptionFlags(CIfrOneOfOption & OOOObj,UINT32 LineNum);
	void oneofoptionFlagsField(UINT8 & HFlags,UINT8 & LFlags);
	void vfrStatementLabel(void);
	void vfrStatementBanner(void);
	void vfrStatementInvalidHidden(void);
	void vfrStatementInvalidInconsistentIf(void);
	void vfrStatementInvalidInventory(void);
	void vfrStatementInvalidSaveRestoreDefaults(void);
	void vfrStatementExpression(UINT32 RootLevel,UINT32 ExpOpCount = 0);
	void vfrStatementExpressionSub(UINT32 RootLevel,UINT32 & ExpOpCount);
	void andTerm(UINT32 & RootLevel,UINT32 & ExpOpCount);
	void bitwiseorTerm(UINT32 & RootLevel,UINT32 & ExpOpCount);
	void bitwiseandTerm(UINT32 & RootLevel,UINT32 & ExpOpCount);
	void equalTerm(UINT32 & RootLevel,UINT32 & ExpOpCount);
	void compareTerm(UINT32 & RootLevel,UINT32 & ExpOpCount);
	void shiftTerm(UINT32 & RootLevel,UINT32 & ExpOpCount);
	void addMinusTerm(UINT32 & RootLevel,UINT32 & ExpOpCount);
	void multdivmodTerm(UINT32 & RootLevel,UINT32 & ExpOpCount);
	void castTerm(UINT32 & RootLevel,UINT32 & ExpOpCount);
	void atomTerm(UINT32 & RootLevel,UINT32 & ExpOpCount);
	void vfrExpressionCatenate(UINT32 & RootLevel,UINT32 & ExpOpCount);
	void vfrExpressionMatch(UINT32 & RootLevel,UINT32 & ExpOpCount);
	void vfrExpressionParen(UINT32 & RootLevel,UINT32 & ExpOpCount);
	void vfrExpressionBuildInFunction(UINT32 & RootLevel,UINT32 & ExpOpCount);
	void dupExp(UINT32 & RootLevel,UINT32 & ExpOpCount);
	void vareqvalExp(UINT32 & RootLevel,UINT32 & ExpOpCount);
	void ideqvalExp(UINT32 & RootLevel,UINT32 & ExpOpCount);
	void ideqidExp(UINT32 & RootLevel,UINT32 & ExpOpCount);
	void ideqvallistExp(UINT32 & RootLevel,UINT32 & ExpOpCount);
	void questionref1Exp(UINT32 & RootLevel,UINT32 & ExpOpCount);
	void rulerefExp(UINT32 & RootLevel,UINT32 & ExpOpCount);
	void stringref1Exp(UINT32 & RootLevel,UINT32 & ExpOpCount);
	void pushthisExp(UINT32 & RootLevel,UINT32 & ExpOpCount);
	void securityExp(UINT32 & RootLevel,UINT32 & ExpOpCount);
	void numericVarStoreType(UINT8 & VarType);
	void getExp(UINT32 & RootLevel,UINT32 & ExpOpCount);
	void vfrExpressionConstant(UINT32 & RootLevel,UINT32 & ExpOpCount);
	void vfrExpressionUnaryOp(UINT32 & RootLevel,UINT32 & ExpOpCount);
	void lengthExp(UINT32 & RootLevel,UINT32 & ExpOpCount);
	void bitwisenotExp(UINT32 & RootLevel,UINT32 & ExpOpCount);
	void question23refExp(UINT32 & RootLevel,UINT32 & ExpOpCount);
	void stringref2Exp(UINT32 & RootLevel,UINT32 & ExpOpCount);
	void toboolExp(UINT32 & RootLevel,UINT32 & ExpOpCount);
	void tostringExp(UINT32 & RootLevel,UINT32 & ExpOpCount);
	void unintExp(UINT32 & RootLevel,UINT32 & ExpOpCount);
	void toupperExp(UINT32 & RootLevel,UINT32 & ExpOpCount);
	void tolwerExp(UINT32 & RootLevel,UINT32 & ExpOpCount);
	void setExp(UINT32 & RootLevel,UINT32 & ExpOpCount);
	void vfrExpressionTernaryOp(UINT32 & RootLevel,UINT32 & ExpOpCount);
	void conditionalExp(UINT32 & RootLevel,UINT32 & ExpOpCount);
	void findExp(UINT32 & RootLevel,UINT32 & ExpOpCount);
	void findFormat(UINT8 & Format);
	void midExp(UINT32 & RootLevel,UINT32 & ExpOpCount);
	void tokenExp(UINT32 & RootLevel,UINT32 & ExpOpCount);
	void spanExp(UINT32 & RootLevel,UINT32 & ExpOpCount);
	void vfrExpressionMap(UINT32 & RootLevel,UINT32 & ExpOpCount);
	void spanFlags(UINT8 & Flags);

private:
UINT8               mParserStatus;
BOOLEAN             mConstantOnlyInExpression;

CVfrDefaultStore    mCVfrDefaultStore;
CVfrDataStorage     mCVfrDataStorage;
CVfrQuestionDB      mCVfrQuestionDB;
CVfrRulesDB         mCVfrRulesDB;

CIfrOpHeader *      mCIfrOpHdr[MAX_IFR_EXPRESSION_DEPTH];
UINT32              mCIfrOpHdrLineNo[MAX_IFR_EXPRESSION_DEPTH];
UINT8               mCIfrOpHdrIndex;
VOID                _SAVE_OPHDR_COND (IN CIfrOpHeader &, IN BOOLEAN, UINT32 LineNo = 0);
VOID                _CLEAR_SAVED_OPHDR (VOID);
BOOLEAN             _SET_SAVED_OPHDR_SCOPE (VOID);


EFI_VARSTORE_INFO   mCurrQestVarInfo;
EFI_GUID            *mOverrideClassGuid;

//
// For framework vfr compatibility
//
BOOLEAN             mCompatibleMode;
EFI_GUID            mFormsetGuid;

VOID                _CRT_OP (IN BOOLEAN);

VOID                _SAVE_CURRQEST_VARINFO (IN EFI_VARSTORE_INFO &);
EFI_VARSTORE_INFO & _GET_CURRQEST_VARTINFO (VOID);

UINT8               _GET_CURRQEST_DATATYPE ();
UINT32              _GET_CURRQEST_VARSIZE ();
UINT32              _GET_CURRQEST_ARRAY_SIZE();

public:
VOID                _PCATCH (IN INTN, IN INTN, IN ANTLRTokenPtr, IN CONST CHAR8 *);
VOID                _PCATCH (IN EFI_VFR_RETURN_CODE);
VOID                _PCATCH (IN EFI_VFR_RETURN_CODE, IN ANTLRTokenPtr);
VOID                _PCATCH (IN EFI_VFR_RETURN_CODE, IN UINT32);
VOID                _PCATCH (IN EFI_VFR_RETURN_CODE, IN UINT32, IN CONST CHAR8 *);

VOID                syn     (ANTLRAbstractToken  *, ANTLRChar *, SetWordType *, ANTLRTokenType, INT32);

CHAR8*              TrimHex (IN CHAR8 *, OUT BOOLEAN *);
CHAR8*              _U32TOS (IN UINT32);
UINT8               _STOU8  (IN CHAR8 *);
UINT16              _STOU16 (IN CHAR8 *);
UINT32              _STOU32 (IN CHAR8 *);
UINT64              _STOU64 (IN CHAR8 *);
EFI_HII_DATE        _STOD   (IN CHAR8 *, IN CHAR8 *, IN CHAR8 *);
EFI_HII_TIME        _STOT   (IN CHAR8 *, IN CHAR8 *, IN CHAR8 *);
EFI_HII_REF         _STOR   (IN CHAR8 *, IN CHAR8 *, IN EFI_GUID *, IN CHAR8 *);

EFI_STRING_ID       _STOSID (IN CHAR8 *);
EFI_FORM_ID         _STOFID (IN CHAR8 *);
EFI_QUESTION_ID     _STOQID (IN CHAR8 *);

VOID                _STRCAT (IN OUT CHAR8 **, IN CONST CHAR8 *);

VOID                _DeclareDefaultLinearVarStore (IN UINT32);
VOID                _DeclareStandardDefaultStorage (IN UINT32);
VOID                _DeclareDefaultFrameworkVarStore (IN UINT32);

VOID                AssignQuestionKey (IN CIfrQuestionHeader &, IN ANTLRTokenPtr);

VOID                ConvertIdExpr         (IN UINT32 &, IN UINT32, IN EFI_QUESTION_ID, IN CHAR8 *, IN UINT32);
VOID                IdEqValDoSpecial      (IN UINT32 &, IN UINT32, IN EFI_QUESTION_ID, IN CHAR8 *, IN UINT32, IN UINT16, IN EFI_COMPARE_TYPE);
VOID                IdEqIdDoSpecial       (IN UINT32 &, IN UINT32, IN EFI_QUESTION_ID, IN CHAR8 *, IN UINT32, IN EFI_QUESTION_ID, IN CHAR8 *, IN UINT32, IN EFI_COMPARE_TYPE);
VOID                IdEqListDoSpecial     (IN UINT32 &, IN UINT32, IN EFI_QUESTION_ID, IN CHAR8 *, IN UINT32, IN UINT16, IN UINT16 *);
VOID                SetOverrideClassGuid  (IN EFI_GUID *);
//
// For framework vfr compatibility
//
VOID                SetCompatibleMode (IN BOOLEAN);
};

#endif /* EfiVfrParser_h */
