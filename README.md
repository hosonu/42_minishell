quotation-bug-handle branchでは

通常の使い方には対応できるようにしたが、それ以外のユースケースではセグフォルトになるので改良する

execveで実行する際にtypeがCOMMAND以上である場合は"" ''を参照する必要があるため除かず、他のtypeでは除く


対応できている機能
    
    ・プロンプト履歴
    
    ・cntl+Cによる改行
    
    ・cntl+Dによる終了

    ・cntl+\で終了しない
    
対応できるプロンプト
    
    ./minishell cmd XX metachar XX ..

    ./minishell metacharacter .. 
    
    ./minishell .. metacharacter

対応できていないプロンプト
    
    "" ''    
    
