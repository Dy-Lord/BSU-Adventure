.486
PUBLIC _AreaSearchone@12
PUBLIC @AreaSearchtwo@12
PUBLIC _AreaSearchthree
.model flat
.data
count dd 0
max dd 0
var dw ?

.code
_AreaSearchone@12 proc
push ebp
mov ebp, esp

push ecx
push ebx
push edx

xor eax, eax
xor esi, esi

mov ebx, [ebp + 8]   ;array
mov edx, [ebp + 12]  ;size
mov ecx, [ebp + 16]  ;param

CT:
mov edx, dword ptr[ebx][esi*4]

mov edi, [ebp + 12]
dec edi

Tolt:

cmp edi, esi
je Lp
mov eax, [ebx][edi*4]
cmp eax, edx
je OP

Lop:
dec edi
jmp Tolt

Lp:
inc esi
cmp esi, [ebp + 12]
jne CT

jmp FL
OP:
xor esi, esi
xor edi, edi

TP:
mov edx, dword ptr[ebx][esi*4]

mov edi, esi
inc edi

TTP:
cmp edx, dword ptr[ebx][edi*4]
jg Y
mov edx, dword ptr[ebx][edi*4]

Y:
inc edi
cmp edi, [ebp + 12]
jne TTP

cmp ecx, 0
je TP

xor edi, edi
mov edi, [ebp + 12]
dec edi

BB:
cmp edx, dword ptr[ebx][edi*4]
jne J
jmp L
J:
push dword ptr[ebx][edi*4]
L:

dec edi
cmp edi, -1
jne BB

mov eax, [ebp + 12]
dec eax
xor edi, edi

HH:
cmp eax, 0
je U
pop dword ptr[ebx][edi*4]
jmp O
U:
mov dword ptr[ebx][edi*4], 0
O:

inc edi
dec eax
cmp edi, [ebp + 12]
jne HH

dec ecx
cmp ecx, 0
jne TP

FL:

pop edx
pop ebx
pop ecx

mov esp, ebp
pop ebp
mov count, 0
ret 12
_AreaSearchone@12 endp



@AreaSearchtwo@12 proc
push ebp
mov ebp, esp

push ecx
push ebx
push edx


pop edx
pop ebx
pop ecx

mov esp, ebp
pop ebp

mov count, 0
ret 4
@AreaSearchtwo@12 endp



_AreaSearchthree proc
push ebp
mov ebp, esp

push ecx
push ebx
push edx

xor eax, eax
xor esi, esi

mov ebx, [ebp + 8]   ;array
mov edx, [ebp + 12]  ;size
mov ecx, [ebp + 16]  ;param

CT:
mov edx, dword ptr[ebx][esi*4]

mov edi, [ebp + 12]
dec edi

Tolt:

cmp edi, esi
je Lp
mov eax, [ebx][edi*4]
cmp eax, edx
je OP

Lop:
dec edi
jmp Tolt

Lp:
inc esi
cmp esi, [ebp + 12]
jne CT

jmp FL
OP:
xor esi, esi
xor edi, edi

TP:
mov edx, dword ptr[ebx][esi*4]

mov edi, esi
inc edi

TTP:
cmp edx, dword ptr[ebx][edi*4]
jg Y
mov edx, dword ptr[ebx][edi*4]

Y:
inc edi
cmp edi, [ebp + 12]
jne TTP

cmp ecx, 0
je TP

xor edi, edi
mov edi, [ebp + 12]
dec edi

BB:
cmp edx, dword ptr[ebx][edi*4]
jne J
jmp L
J:
push dword ptr[ebx][edi*4]
L:

dec edi
cmp edi, -1
jne BB

mov eax, [ebp + 12]
dec eax
xor edi, edi

HH:
cmp eax, 0
je U
pop dword ptr[ebx][edi*4]
jmp O
U:
mov dword ptr[ebx][edi*4], 0
O:

inc edi
dec eax
cmp edi, [ebp + 12]
jne HH

dec ecx
cmp ecx, 0
jne TP

FL:

pop edx
pop ebx
pop ecx

mov esp, ebp
pop ebp
mov count, 0
ret
_AreaSearchthree endp

end