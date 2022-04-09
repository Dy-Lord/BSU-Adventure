.486
PUBLIC _AreaSearchone@16
PUBLIC @AreaSearchtwo@16
PUBLIC _AreaSearchthree
.model flat
.data
count dd 0
var dw ?

.code
_AreaSearchone@16 proc
push ebp
mov ebp, esp

push ecx
push ebx
push edx

xor eax, eax

mov ebx, [ebp + 8]   
mov edx, [ebp + 12]  
mov ecx, [ebp + 16]  

push [ebp + 20] 
pop var

xor esi, esi
xor edi, edi 

up:

mov ax, word ptr [ebx][esi*2]

cmp ax, var
jge cont

neg var

cmp ax, var
jle ncont


mov [edx][edi*2], ax
inc count
inc edi

ncont:
neg var

cont:

inc esi
cmp esi, ecx

jne up

mov eax, count

pop edx
pop ebx
pop ecx

mov esp, ebp
pop ebp
mov count, 0
ret 16
_AreaSearchone@16 endp

@AreaSearchtwo@16 proc
push ebp
mov ebp, esp

push ecx
push ebx
push edx

xor eax, eax

mov ebx, ecx    
mov ecx, [ebp + 8]  

push [ebp + 12] 
pop var

xor esi, esi
xor edi, edi 

up:

mov ax, word ptr [ebx][esi*2]

cmp ax, var
jge cont

neg var

cmp ax, var
jle ncont


mov [edx][edi*2], ax
inc count
inc edi

ncont:
neg var

cont:

inc esi
cmp esi, ecx

jne up

mov eax, count

pop edx
pop ebx
pop ecx

mov esp, ebp
pop ebp

mov count, 0
ret 8
@AreaSearchtwo@16 endp


_AreaSearchthree proc
push ebp
mov ebp, esp

push ecx
push ebx
push edx

xor eax, eax

mov ebx, [ebp + 8]   
mov edx, [ebp + 12]  
mov ecx, [ebp + 16]  

push [ebp + 20] 
pop var

xor esi, esi
xor edi, edi 

up:

mov ax, word ptr [ebx][esi*2]

cmp ax, var
jge cont

neg var

cmp ax, var
jle ncont


mov [edx][edi*2], ax
inc count
inc edi

ncont:
neg var

cont:

inc esi
cmp esi, ecx

jne up

mov eax, count

pop edx
pop ebx
pop ecx

mov esp, ebp
pop ebp

mov count, 0
ret
_AreaSearchthree endp

end