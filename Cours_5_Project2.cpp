#include <iostream>

using namespace std;


/////////////////////////////////   Quize Math Game   //////////////////////////////////////////////////////////////////////////
int RandNumber(int From, int To)
{
    int RandNum = rand() % (To - From + 1) + From;
    return RandNum;
}

enum enQuestionLevel {EasyLevel = 1, MedLevel = 2, HardLevel = 3, Mix = 4};
enum enQuestionOpType { Add = 1, Sub = 2, Mul = 3, Div = 4, MixOp = 5};

struct strQuestion
{
    int Number1;
    int Number2;
    enQuestionLevel QuestionLevel;
    enQuestionOpType QuestionOpType;
    short CorrectAnswer;
    short PlayerAnswer;
    bool AnswerResult = true;
};

struct strQuizz
{
    strQuestion QuestionList[100];
    short NumberOfQuestions;
    enQuestionLevel QuestionLevel;
    enQuestionOpType QuestionOpType;
    short NumberOfWrongAnswers = 0;
    short NumberOfRightAnswers = 0;
    bool isPass;
};

void SetScreenPassQuizz(bool isPass)
{
    if(isPass)
        system("color 2F");
    else
    {
        system("color 4F");
        cout << "\a";
    }
}

string GetOpTypeSymbol(enQuestionOpType OpType)
{
    switch (OpType)
    {
    case enQuestionOpType::Add:
        return "+";

    case enQuestionOpType::Sub:
        return "-";

    case enQuestionOpType::Mul:
        return "*";

    case enQuestionOpType::Div:
        return "/";

    case enQuestionOpType::MixOp:
        return "Mix";
    
   
    }
}
void PrintQuestion(strQuizz& Quizz, short QuestionNumber)
{
    cout << endl;
    cout << "Question [" << QuestionNumber + 1<< " / " << Quizz.NumberOfQuestions << "]\n" << endl;
    cout << Quizz.QuestionList[QuestionNumber].Number1 << endl << Quizz.QuestionList[QuestionNumber].Number2;
    cout << "  " << GetOpTypeSymbol(Quizz.QuestionList[QuestionNumber].QuestionOpType) << endl;
    cout << "_______\n";


}
short ReadPlayerAnswer()
{
    short PlayerAnswer;
    cin >> PlayerAnswer;

    return PlayerAnswer;
}

void CorrectQuestionAnswer(strQuizz& Quizz, short NumberOfQuestions)
{
    if (Quizz.QuestionList[NumberOfQuestions].PlayerAnswer == Quizz.QuestionList[NumberOfQuestions].CorrectAnswer)
    {
        Quizz.QuestionList[NumberOfQuestions].AnswerResult = true;
        Quizz.NumberOfRightAnswers++;

        cout << "RightAnswer :-)\n" << endl;
        
    }
    else

    {
        Quizz.QuestionList[NumberOfQuestions].AnswerResult = false;
        Quizz.NumberOfWrongAnswers++;
        cout << "Wrong Answer :-(\n";
        cout << "The correct Answer is : " << Quizz.QuestionList[NumberOfQuestions].CorrectAnswer << endl << endl;
    }
    cout << endl;
    SetScreenPassQuizz(Quizz.QuestionList[NumberOfQuestions].AnswerResult);

}
void AskUserAndCorrectAnswer(strQuizz& Quizz)
{
    for (short QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestions; QuestionNumber++)
    {
        PrintQuestion(Quizz, QuestionNumber);

        Quizz.QuestionList[QuestionNumber].PlayerAnswer = ReadPlayerAnswer();

        CorrectQuestionAnswer(Quizz, QuestionNumber);
    }

    Quizz.isPass = (Quizz.NumberOfRightAnswers >= Quizz.NumberOfWrongAnswers);
}
short SimpleCalculator(short Number1, short Number2, enQuestionOpType OpType)
{
    switch (OpType)
    {
    case enQuestionOpType::Add:
        return Number1 + Number2;

    case enQuestionOpType::Sub:
        return Number1 - Number2;

    case enQuestionOpType::Mul:
        return Number1 * Number2;

    case enQuestionOpType::Div:
        if (Number2 != 0)
            return Number1 / Number2;
        else
            return 0;
    default:
        return Number1 + Number2;
    }
}
enQuestionOpType GetRandomOperationType()
{
    return (enQuestionOpType)RandNumber(1, 4);
}
strQuestion GenerateQuestion(enQuestionLevel QuestionLevel, enQuestionOpType OpType)
{
    strQuestion Question;
    if (QuestionLevel == enQuestionLevel::Mix)
        QuestionLevel = (enQuestionLevel)RandNumber(1, 3);

    if (OpType == enQuestionOpType::MixOp)
        OpType = GetRandomOperationType();

    Question.QuestionOpType = OpType;


    switch (QuestionLevel)
    {
    case enQuestionLevel::EasyLevel:
        Question.Number1 = RandNumber(1, 10);
        Question.Number2 = RandNumber(1, 10);
        Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.QuestionOpType);

        Question.QuestionLevel = QuestionLevel;
        return Question;


    case enQuestionLevel::MedLevel:
        Question.Number1 = RandNumber(10, 20);
        Question.Number2 = RandNumber(10, 20);
        Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.QuestionOpType);

        Question.QuestionLevel = QuestionLevel;
        return Question;


    case enQuestionLevel::HardLevel:
        Question.Number1 = RandNumber(20, 30);
        Question.Number2 = RandNumber(20, 30);
        Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.QuestionOpType);

        Question.QuestionLevel = QuestionLevel;
        return Question;
    }
}
void GenerateQuizzQuestions(strQuizz& Quizz)
{
    for (int Question = 0; Question < Quizz.NumberOfQuestions; Question++)
    {
        Quizz.QuestionList[Question] = GenerateQuestion(Quizz.QuestionLevel, Quizz.QuestionOpType);
    }
}

short ReadHowManyQuestions()
{
    short NumberOfQuestions;

        cout << "How Many Questions Do you want to answer? ";
        cin >> NumberOfQuestions;
   

    return NumberOfQuestions;
}
enQuestionLevel GetQuestionLevel()
{
    short QuestionLevel;

    do
    {
        cout << "Enter the Level of Questions:  Easy[1], Med[2], Hard[3], Mix[4]: ";
        cin >> QuestionLevel;
    } while (QuestionLevel < 0 || QuestionLevel > 4);

    return (enQuestionLevel) QuestionLevel;
}
enQuestionOpType GetQuestionOperationType()
{
    short QuestionOp;

    do
    {
        cout << "Enter the Type of Operation:  Add[1], Sub[2], Mul[3], Div[4], Mix[5]: ";
        cin >> QuestionOp;
    } while (QuestionOp < 0 || QuestionOp > 5);

    return (enQuestionOpType)QuestionOp;
}

string GetFinalResultText(bool isPass)
{
    if (isPass)
        return "Pass";
    else
        return "Faill";
}
bool isPass(strQuizz Quizz)
{
    return (Quizz.NumberOfRightAnswers > Quizz.NumberOfWrongAnswers);
}
string GetQuestionLevelText(enQuestionLevel QuestionLevel)
{
    string arrQuestionLevelText[4] = { "Easy", "Med", "Hard", "Mix" };
    return arrQuestionLevelText[QuestionLevel - 1];
    
}
void PrintFinalResult(strQuizz Quizz)
{
    cout << "_______________________________\n";
    cout << "\t\t" << GetFinalResultText(Quizz.isPass) << endl;
    cout << "_______________________________\n";

    cout << "Number of Questions    : " << Quizz.NumberOfQuestions << endl;
    cout << "Question  Level        : " << GetQuestionLevelText(Quizz.QuestionLevel) << endl;
    cout << "Question  Operation    : " << GetOpTypeSymbol(Quizz.QuestionOpType) << endl;
    cout << "Number Of Right Answers: " << Quizz.NumberOfRightAnswers << endl;
    cout << "Number of Wrong Answers: " << Quizz.NumberOfWrongAnswers << endl;
    cout << "_______________________________\n\n";

    SetScreenPassQuizz(Quizz.isPass);
}
void PlayMathGame()
{
    strQuizz Quizz;
    Quizz.NumberOfQuestions = ReadHowManyQuestions();
    Quizz.QuestionLevel = GetQuestionLevel();
    Quizz.QuestionOpType = GetQuestionOperationType();

    GenerateQuizzQuestions(Quizz);
    AskUserAndCorrectAnswer(Quizz);

    PrintFinalResult(Quizz);
}

void ResetScreen()
{
    system("cls");
    system("color 0F");
}

void StartGame()
{
    char PlayAgain = 'Y';

    do
    {
        ResetScreen();
        PlayMathGame();
        cout << "\n\nDo you want to Play Again [Y] / [N] : ";
        cin >> PlayAgain;
    } while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
    srand((unsigned)time(NULL));

    StartGame();
}
