#include "comp.h"

Comp::Comp() : Ak::Component("Kila tester component") {}

void Comp::onAttach()
{
    std::cout << "Running..." << std::endl;
}

void Comp::onEvent(Ak::Input& input)
{
    input.finish();
}

void Comp::update()
{
    
    Ak::Kl::File f(std::string(Ak::Core::getMainDirPath() + "Tests/Kila/test.ksl").c_str());
    func::function<int()> get = [&](){ return f(); };
    Ak::Kl::StreamStack stream(&get);
    Ak::Kl::tk_iterator it(stream);

    for(; it(); it++)
    {
        if(it->is_keyword())
        {
            if(Ak::Kl::Token::kw_tokens.have(it->get_token()))
            {
                std::cout << "Keyword    : ";
                std::cout << Ak::Kl::Token::kw_tokens[it->get_token()] << std::endl;
            }
            else if(Ak::Kl::Token::operators_token.have(it->get_token()))
            {
                std::cout << "Operator   : ";
                std::cout << Ak::Kl::Token::operators_token[it->get_token()] << std::endl;
            }
        }
        if(it->is_number())
            std::cout << "Number     : " << it->get_number() << std::endl;
        if(it->is_identifier())
            std::cout << "Identifier : " << it->get_identifier().name << std::endl;
    }
    std::cout << "end of file" << std::endl;
    
    /*
    Ak::BinarySearchTree<int> tree(20);
    tree.add(15);
    tree.add(7);
    tree.add(19);
    tree.add(16);
    tree.add(40);
    tree.add(60);
    tree.add(50);
    tree.add(70);
    tree.remove(60);
    std::cout << "test : " << tree.find_parent(19)->getData() << std::endl;
    */
    //Ak::Core::log::report(FATAL_ERROR, "breaker");
}

void Comp::onQuit()
{
    std::cout << "End" << std::endl;
}
