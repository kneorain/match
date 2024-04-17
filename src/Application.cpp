#include "Application.hpp"
#include "Logs/Logs.hpp"
#include "Tokeniser/Tokeniser.hpp"
namespace Match
{
    Application::Application()
    {
        run();
    }

    Application::~Application()
    {
        
    }

    void Application::run()
    {

        Tokenizer tokenizer;
        SlideViewChar source = SlideViewChar("Hello World");
        tokenizer.Tokenize(source);
        LOG_INFO("Token: {}", token.GetSubTokensAsStr());
    
    }
}