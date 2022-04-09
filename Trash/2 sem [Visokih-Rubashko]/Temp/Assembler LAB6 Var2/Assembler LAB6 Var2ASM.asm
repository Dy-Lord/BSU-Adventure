.486

PUBLIC _matrixswtitch1@12
PUBLIC _matrixswtitch2
PUBLIC @matrixswtitch3@12

.model flat

.code
_matrixswtitch1@12 proc

push ebp
mov ebp, esp

push ecx
push edx
push esi

xor eax, eax
xor edi, edi

mov ecx, [ebp + 8]   
mov edx, [ebp + 12]  
mov esi, [ebp + 16]  

imul edx, 4
imul esi, edx
add ecx, esi
mov edi, [ebp + 12]
dec edi

_while:
push [ecx][edi*4]
dec edi
cmp edi, -1
jne _while

mov ecx, [ebp + 8] 
mov esi, [ebp + 12]
dec esi
imul esi, edx
add ecx, esi
mov edi, [ebp + 16]

mov eax, [ebp + 12]
dec eax

_whilecol:
push [ecx][edi*4]
sub ecx, edx
dec eax
cmp eax, -1
jne _whilecol

mov ecx, [ebp + 8]
mov esi, [ebp + 16] 
imul esi, edx
add ecx, esi
xor edi, edi


_whilestr:
pop [ecx][edi*4]
inc edi
cmp edi, [ebp + 12]
jne _whilestr

mov edi, [ebp + 16]
mov ecx, [ebp + 8]
xor eax, eax

_for:
pop [ecx][edi*4]
add ecx, edx
inc eax
cmp eax, [ebp + 12]
jne _for

pop esi
pop edx
pop ecx

mov esp, ebp
pop ebp

ret 12
_matrixswtitch1@12 endp

_matrixswtitch2 proc
push ebp
mov ebp, esp

push ecx
push edx
push esi

xor eax, eax
xor edi, edi

mov ecx, [ebp + 8]   
mov edx, [ebp + 12]  
mov esi, [ebp + 16]  

imul edx, 4
imul esi, edx
add ecx, esi
mov edi, [ebp + 12]
dec edi

_while:
push [ecx][edi*4]
dec edi
cmp edi, -1
jne _while

mov ecx, [ebp + 8] 
mov esi, [ebp + 12]
dec esi
imul esi, edx
add ecx, esi
mov edi, [ebp + 16]

mov eax, [ebp + 12]
dec eax

_whilecol:
push [ecx][edi*4]
sub ecx, edx
dec eax
cmp eax, -1
jne _whilecol

mov ecx, [ebp + 8]
mov esi, [ebp + 16] 
imul esi, edx
add ecx, esi
xor edi, edi


_whilestr:
pop [ecx][edi*4]
inc edi
cmp edi, [ebp + 12]
jne _whilestr

mov edi, [ebp + 16]
mov ecx, [ebp + 8]
xor eax, eax

_for:
pop [ecx][edi*4]
add ecx, edx
inc eax
cmp eax, [ebp + 12]
jne _for

pop esi
pop edx
pop ecx

mov esp, ebp
pop ebp

ret
_matrixswtitch2 endp


@matrixswtitch3@12 proc
push ebp
mov ebp, esp

push ecx
push edx
push esi

xor edi, edi

mov eax, ecx
mov ebx, edx

;mov ecx, [ebp + 8]   
;mov edx, [ebp + 12]  
mov esi, [ebp + 8]  

imul edx, 4
imul esi, edx
add ecx, esi
mov edi, ebx
dec edi

_while:
push [ecx][edi*4]
dec edi
cmp edi, -1
jne _while

mov ecx, eax
mov esi, ebx
dec esi
imul esi, edx
add ecx, esi
mov edi, [ebp + 8]

mov esi, ebx
dec esi

_whilecol:
push [ecx][edi*4]
sub ecx, edx
dec esi
cmp esi, -1
jne _whilecol

mov ecx, eax
mov esi, [ebp + 8] 
imul esi, edx
add ecx, esi
xor edi, edi

_whilestr:
pop [ecx][edi*4]
inc edi
cmp edi, ebx
jne _whilestr

mov edi, [ebp + 8]
mov ecx, eax
xor esi, esi

_for:
pop [ecx][edi*4]
add ecx, edx
inc esi
cmp esi, ebx
jne _for

pop esi
pop edx
pop ecx

mov esp, ebp
pop ebp

ret 4
@matrixswtitch3@12 endp

end