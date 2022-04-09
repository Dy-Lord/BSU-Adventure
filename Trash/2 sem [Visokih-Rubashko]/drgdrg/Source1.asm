.486
PUBLIC @deletelr@16
PUBLIC _deletelr1@16
PUBLIC _deletelr2
.model flat
.data
count dd 0
right db ?
left db ?
.code
@deletelr@16 proc

push ebp
mov ebp, esp

mov ebx, ecx ;array
mov esi, edx ;size
dec esi

xor eax, eax
xor edi, edi
mov ch, 0

m1:

mov al ,[ebx][esi*1]
cmp al,0
jg Lk
neg al
Lk:
cmp al, [ebp + 12]
jg m3
cmp al, [ebp + 8]
jl m3
jmp m2

m3:
inc count
push [ebx][esi*1]

m2:
dec esi
cmp esi, -1
jne m1

xor esi, esi

Co:

cmp esi, count
jl STk
mov [ebx][esi*1], ch
jmp F

STk:
pop [ebx][esi*1]

F:
inc esi
cmp esi, edx
jne Co

mov eax, 1

mov esp, ebp
pop ebp
mov count, 0
ret 8
@deletelr@16 endp




_deletelr1@16 proc

push ebp
mov ebp, esp

mov ebx, [ebp + 8] ;array
mov esi, [ebp + 12] ;size
dec esi

xor eax, eax
xor edi, edi
mov ch, 0

m1:

mov al ,[ebx][esi*1]
cmp al,0
jg Lk
neg al
Lk:
cmp al, [ebp + 20]
jg m3
cmp al, [ebp + 16]
jl m3
jmp m2

m3:
inc count
push [ebx][esi*1]

m2:
dec esi
cmp esi, -1
jne m1

xor esi, esi

Co:

cmp esi, count
jl STk
mov [ebx][esi*1], ch
jmp F

STk:
pop [ebx][esi*1]

F:
inc esi
cmp esi, [ebp + 12]
jne Co

mov eax, 1

mov esp, ebp
pop ebp
mov count, 0
ret 16
_deletelr1@16 endp

_deletelr2 proc

push ebp
mov ebp, esp

mov ebx, [ebp + 8] ;array
mov esi, [ebp + 12] ;size
dec esi

xor eax, eax
xor edi, edi
mov ch, 0

m1:

mov al ,[ebx][esi*1]
cmp al,0
jg Lk
neg al
Lk:
cmp al, [ebp + 20]
jg m3
cmp al, [ebp + 16]
jl m3
jmp m2

m3:
inc count
push [ebx][esi*1]

m2:
dec esi
cmp esi, -1
jne m1

xor esi, esi

Co:

cmp esi, count
jl STk
mov [ebx][esi*1], ch
jmp F

STk:
pop [ebx][esi*1]

F:
inc esi
cmp esi, [ebp + 12]
jne Co

mov eax, 1

mov esp, ebp
pop ebp
mov count, 0
ret 
_deletelr2 endp
end