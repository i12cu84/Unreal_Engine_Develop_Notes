```
编辑任意一次提交:
    1.  git rebase -i HEAD-n 从当前位置往回偏移n次
        git rebase -i HEAD^^^^ 从当前位置往回偏移四次(对应四个^)
    2.将漏提交或已修改的文件添加到暂存区git add <漏交的文件路径>
        默认在命令模式按一次小写i 进入编辑模式
        输入完成 按一次ESC回到命令模式
        输入两次大写Z保存退出
        ->覆盖当前提交 git commit --amend
    3.变基到最后 git rebase --continue

回退某一次提交:
    1.查询你要回退的提交的code git log
    2.  git rebase -i HEAD ~n 从当前位置往回偏移n次
        git rebase -i HEAD^^^^ 从当前位置往回偏移四次(对应四个^)
        ->变基到你要回退的那一次提交 git rebase -i HEAD~2
    3.生成一次与对应提交刚好相反的提交 git revertHEAD<commit SHA-1 code>
    4.git push

文件修改撤销:
    1.查看文件修改状态 git status
    2.单个文件 git reset HEAD XXX.js
    3.所有未提交的文件 git reset --hard

暂存区添加撤销:
    1.查看暂存区状态 git status
    2.git reset HEAD <要移除的文件路径>

撤销分支删除:
    1.找到已删除分支的引用 code git reflog
    2.撤销并切换到对应分支
        git checkout <branch-code>
        git checkout -b <删除的分支名>
    
报错:LF will be replaced by CRLF the next time Git touches it
    1.git config --global core.autocrlf true
    解决方案:https://blog.csdn.net/u012757419/article/details/105614028
    
```