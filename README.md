//Bでは連結リストのトークンを線形リストにして実行順に並び変える

//リダイレクトによりファイルトークンにコマンドがはいっている場合は切り離して挿入する

//この時にシンタックスエラー出したいがその処理はまた今度やる

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
    
