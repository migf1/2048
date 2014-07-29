unit u_replay;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils;

Type
	TBoard=Array of Integer;
  pBoard=^TBoard;
	TState=Record
    win,prev,next:Integer;
    board:pBoard;
    End;
	pState=^TState;

TReplay=class
  private
    FDim:Integer;
    FState:pBoard;
  protected
    function GetDim:Integer;
    function GetState:pBoard;
  public
	  Constructor Create;
  	Function LoadFromFile(FileName:String):Boolean;
  	Destructor Destroy; Override;
    property Dim:Integer read GetDim default 0;
    // temp
    property State:pBoard read GetState;
  End;

implementation

Function CreateState(win,prev,next:Integer;board:pBoard):pState;
Begin
Result:=new(pState);
Result^.win:=win;
Result^.prev:=prev;
Result^.next:=next;
Result^.board:=board;
End;

Function BoardFromString(s:String):pBoard;
Var
	sl:TStringList;
  i:Integer;
Begin
sl:=TStringList.Create;
sl.Delimiter:=' ';
sl.DelimitedText:=s;
//SetLength(Result^,sl.Count);
{
GetMem(Result,sl.Count*Sizeof(Integer));
For i:=0 to sl.Count-1 do
	Result^[i]:=StrToInt(sl.Strings[i]);
}
sl.Free;
end;

// getters

Function TReplay.GetDim:Integer; Begin Result:=FDim; End;
Function TReplay.GetState:pBoard; Begin Result:=FState; End;

Constructor TReplay.Create;
Begin
FState:=BoardFromString('8 0 0 0 1 0 0 2 0 4 0 0 3 0 0 0');
end;

Function TReplay.LoadFromFile(FileName:String):Boolean;
Var
	sav:TStringList;
Begin
sav:=TStringList.Create;
With sav do
	Begin
  LoadFromFile(FileName);
  End;
Result:=True;
end;

Destructor TReplay.Destroy;
Begin
Inherited;
///
end;

end.

