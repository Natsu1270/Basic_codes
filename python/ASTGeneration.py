from MCVisitor import MCVisitor
from MCParser import MCParser
from AST import *

    #moi luat van pham thi se co 1 ham visit
    # #luat program:...->visitProgram:(upper p) <qui dinh cua Antlr)
    # #visit ProgramContext( noi dung cua not program)
class ASTGeneration(MCVisitor):
    def visitProgram(self,ctx:MCParser.ProgramContext):
        lst=[]
        j=ctx.getChildCount()
        #if not ctx.funcdecl(): 
        for x in ctx.vardecl():
            lst=lst+(self.visit(x))
        #elif not ctx.vardecl():
        for x in ctx.funcdecl():
            lst.append(self.visit(x))
        return Program(lst)
    def visitVardecl(self,ctx:MCParser.VardeclContext):
        #lst=VarDecl(self.visit(ctx.var_(0)),self.visit(ctx.primitive_type()))
        lst=[]
        for x in ctx.var_():
            if x.getChildCount()==1:
                a=self.visit(ctx.primitive_type())
            else:
                a=ArrayType(int(IntLiteral(x.INTLIT().getText())))
            lst.append(VarDecl((self.visit(x)),a))
        return lst

    def visitVar_(self,ctx:MCParser.Var_Context):
        return Id(ctx.ID().getText())

    def visitPrimitive_type(self,ctx:MCParser.Primitive_typeContext):
        if ctx.BOOLEANTYPE():
            return BoolType
        elif ctx.INTTYPE():
            return IntType
        elif ctx.FLOATTYPE():
            return FloatType
        else:
            return StringType

    #name: Id
    #param: list(VarDecl)
    #returnType: Type
    #body: Block
    #funcdecl : funcreturn_type ID LBR paralist? RBR blockstmt
    def visitFuncdecl(self,ctx:MCParser.FuncdeclContext):
        return FuncDecl(Id(ctx.ID().getText()),(self.visit(ctx.paralist()) if ctx.paralist() else []),
            self.visit(ctx.funcreturn_type()),self.visit(ctx.blockstmt()))

    def visitParalist(self,ctx:MCParser.ParalistContext):
        return [self.visit(x) for x in ctx.paradecl()]

    def visitParadecl(self,ctx:MCParser.ParadeclContext):
        if ctx.getChildCount()==2:
            return VarDecl(Id(ctx.ID().getText()),self.visit(ctx.primitive_type()))
        else:
            return self.visit(ctx.in_array_ptr_type())

    def visitFuncreturn_type(self,ctx:MCParser.Funcreturn_typeContext):
        if ctx.primitive_type():
            return self.visit(ctx.primitive_type())
        elif ctx.out_array_ptr_type():
            return self.visit(ctx.out_array_ptr_type())
        else:
            return VoidType

    def visitIn_array_ptr_type(self,ctx:MCParser.In_array_ptr_typeContext):
        arr_type=ArrayPointerType(self.visit(ctx.primitive_type()))
        return VarDecl(Id(ctx.ID().getText()),arr_type)

    def visitOut_array_ptr_type(self,ctx:MCParser.Out_array_ptr_typeContext):
        return ArrayPointerType(self.visit(ctx.primitive_type()))

    def visitBlockstmt(self,ctx:MCParser.BlockstmtContext):
        var_part=[self.visit(x) for x in ctx.vardecl()] if ctx.vardecl() else []
        stmt_part=[self.visit(x) for x in ctx.stmt()] if ctx.stmt() else []
        return Block(var_part,stmt_part)

    def visitStmt(self,ctx:MCParser.StmtContext):
        if ctx.matchstmt():
            return self.visit(ctx.matchstmt())
        else:
            return self.visit(ctx.unmatchstmt())

    def visitMatchstmt(self,ctx:MCParser.MatchstmtContext):
        if ctx.getChildCount()==7:
            return If(self.visit(ctx.expr()),self.visit(ctx.matchstmt(0)),self.visit(ctx.matchstmt(1)))
        else:
            return self.visit(ctx.otherstmt())

    def visitUnmatchstmt(self,ctx:MCParser.UnmatchstmtContext):
        if ctx.getChildCount()==5:
            return If(self.visit(ctx.expr()),self.visit(ctx.stmt()))
        else:
            return If(self.visit(ctx.expr()),self.visit(ctx.stmt(0)),self.visit(ctx.stmt(1)))

    def visitOtherstmt(self,ctx:MCParser.OtherstmtContext):
        if ctx.dowhilestmt():
            return self.visit(ctx.dowhilestmt())
        elif ctx.forstmt():
            return self.visit(ctx.forstmt())
        elif ctx.breakstmt():
            return self.visit(ctx.breakstmt())
        elif ctx.continuestmt():
            return self.visit(ctx.continuestmt())
        elif ctx.returnstmt():
            return self.visit(ctx.returnstmt())
        elif ctx.exprstmt():
            return self.visit(ctx.exprstmt())
        else:
            return self.visit(ctx.blockstmt())

    def visitDowhilestmt(self,ctx:MCParser.DowhilestmtContext):
        return Dowhile([self.visit(x) for x in ctx.stmt()],self.visit(ctx.expr()))

    def visitForstmt(self,ctx:MCParser.ForstmtContext):
        return For(self.visit(ctx.expr(0)),self.visit(ctx.expr(1)),self.visit(ctx.expr(2)),self.visit(ctx.stmt()))

    def visitBreakstmt(self,ctx:MCParser.BreakstmtContext):
        return Break

    def visitContinuestmt(self,ctx:MCParser.ContinuestmtContext):
        return Continue

    def visitReturnstmt(self,ctx:MCParser.ReturnstmtContext):
        if not ctx.expr():
            return None
        else:
            return Return(Some(self.visit(ctx.expr)))

    def visitExprstmt(self,ctx:MCParser.ExprstmtContext):
        return self.visit(ctx.expr())

    def visitFunccall(self,ctx:MCParser.FunccallContext):
        return CallExpr(Id(ctx.ID().getText()),(self.visit(ctx.explist()) if ctx.explist() else []))

    def visitExplist(self,ctx:MCParser.ExplistContext):
        return [self.visit(x) for x in expr()]

    def visitExpr(self,ctx:MCParser.ExprContext):
        if ctx.getChildCount()==3:
            return BinaryOp("=",self.visit(ctx.getChild(0)),self.visit(ctx.expr()))
        else:
            return self.visit(ctx.getChild(0))

    def visitExpr1(self,ctx:MCParser.Expr1Context):
        if ctx.getChildCount()==3:
            return BinaryOp("||",self.visit(ctx.expr1()),self.visit(ctx.expr2()))
        else:
            return self.visit(ctx.expr2())

    def visitExpr2(self,ctx:MCParser.Expr2Context):
        if ctx.getChildCount()==3:
            return BinaryOp("&&",self.visit(ctx.expr2()),self.visit(ctx.expr3))
        else:
            return self.visit(ctx.expr3())

    def visitExpr3(self,ctx:MCParser.Expr3Context):
        if ctx.getChildCount()==3:
            if ctx.EQOP():
                return BinaryOp(ctx.EQOP().getText(),self.visit(ctx.expr4(0)),self.visit(ctx.epxr4(1)))
            else:
                return BinaryOp(ctx.NEQOP().getText(),self.visit(ctx.expr4(0)),self.visit(ctx.expr4(1)))
        else:
            return self.visit(ctx.expr4())

    def visitExpr4(self,ctx:MCParser.Expr4Context):
        if ctx.getChildCount()==3:
            return BinaryOp(ctx.getChild(1).getText(),self.visit(ctx.expr5(0)),self.visit(ctx.expr5(1)))
        else:
            return self.visit(ctx.expr5())

    def visitExpr5(self,ctx:MCParser.Expr5Context):
        if ctx.getChildCount()==3:
            return BinaryOp(ctx.getChild(1).getText(),self.visit(ctx.expr5()),self.visit(ctx.expr6()))
        else:
            return self.visit(ctx.expr6())

    def visitExpr6(self,ctx:MCParser.Expr6Context):
        if ctx.getChildCount()==3:
            return BinaryOp(ctx.getChild(1).getText(),self.visit(ctx.expr6()),self.visit(ctx.expr7()))
        else:
            return self.visit(ctx.expr7())

    def visitExpr7(self,ctx:MCParser.Expr7Context):
        if ctx.getChildCount()==2:
            return UnaryOp(ctx.getChild(0).getText(),self.visit(ctx.expr7()))
        else:
            return self.visit(ctx.expr8())

    def visitExpr8(self,ctx:MCParser.Expr8Context):
        if ctx.expr():
            return ArrayCell(self.visit(ctx.expr8()),self.visit(ctx.expr()))
        else:
            return self.visit(ctx.expr9())

    def visitExpr9(self,ctx:MCParser.Expr9Context):
        if ctx.litterals():
            return self.visit(ctx.litterals())
        elif ctx.ID():
            return Id(ctx.ID().getText())
        elif ctx.funccall():
            return self.visit(ctx.funccall())
        else:
            return self.visit(ctx.expr())

    def visitLiterals(self,ctx:MCParser.LiteralsContext):
        if ctx.INTLIT():
            return IntLiteral(int(ctx.INTLIT().getText()))
        elif ctx.BOOLLIT():
            return BooleanLiteral(bool(ctx.BOOLLIT().getText()))
        elif ctx.FLOATLIT():
            return FloatLiteral(float(ctx.FLOATLIT().getText()))
        else:
            return StringLiteral(ctx.STRINGLIT().getText())






    








    


























