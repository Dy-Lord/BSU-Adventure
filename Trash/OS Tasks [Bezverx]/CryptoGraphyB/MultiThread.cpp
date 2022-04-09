// commit line - debug lines for additional info
#include <fstream>
#include <sstream>
#include <thread>
#include <chrono>
#include <iostream>
#include <Windows.h>
#include <string>
#include <exception>
#include <vector>
#include <List>
#include <mutex>
#include <stack>
#include <random>

using namespace std;
void encryption(int);

class Timer {
private:
	chrono::time_point<chrono::high_resolution_clock> start;

public:
	Timer() {
	}

	void startTimer() {
		start = chrono::high_resolution_clock::now();
	}

	void resetTimer() {
		start = chrono::high_resolution_clock::now();
	}

	double getTime() {
		return chrono::duration_cast<chrono::duration<double, std::ratio<1>>> (chrono::high_resolution_clock::now() - start).count();
	}

};

class safetyStack{
	recursive_mutex lock;
	stack<pair<string, string>> box;
public:
	void push(string input, string config)
	{
		lock_guard<recursive_mutex> locker(lock);
		box.push(make_pair(input, config));
	}

	bool pop(pair<string, string>& pr) {
		lock_guard<recursive_mutex> locker(lock);
		if (box.size() == 0)
			return false;

		pr = box.top();
		box.pop();

		return true;
	}

	int getTop() {
		lock_guard<recursive_mutex> locker(lock);
		return box.size();
	}
};

struct xxxThread {
private:
	int threadID;

	Timer time;
	double workTime = 0;
	double maxSolveTime = 0;
	double minSolveTime = 0;

	int solveTasks = 0;
	int unsolveTasks = 0;
	int errorTasks = 0;

	bool isAlive;

public:
	xxxThread(int ID) {
		threadID = ID;
		time.startTimer();
		isAlive = true;
	}

	bool getAlive() {
		return isAlive;
	}

	double getWorkTime() {
		return workTime;
	}

	double getMaxSolveTime() {
		return maxSolveTime;
	}

	double getMinSolveTime() {
		return minSolveTime;
	}

	int getSolveTasks() {
		return solveTasks;
	}

	int getUnsolveTasks() {
		return unsolveTasks;
	}

	int getErrorTasks() {
		return errorTasks;
	}

	int getThreadID() {
		return threadID;
	}

	void startThread() {
		thread encryptThread(encryption, this->getThreadID());
		SetThreadPriority(encryptThread.native_handle(), THREAD_PRIORITY_BELOW_NORMAL);
		encryptThread.detach();
	}

	void setIsCloseFlag() {
		isAlive = false;
		workTime = time.getTime();
	}

	void taskIsSolve(double time) {
		solveTasks++;

		if (maxSolveTime == 0 || maxSolveTime < time)
			maxSolveTime = time;

		if (minSolveTime == 0 || minSolveTime > time)
			minSolveTime = time;
	}

	void taskUnsolve() {
		unsolveTasks++;
	}

	void taskWithError() {
		errorTasks++;
	}
};

class safetyVector {
private:
	recursive_mutex lock;
	vector<xxxThread> Threads;

public:

	void push_back(xxxThread tr)
	{
		lock_guard<recursive_mutex> locker(lock);
		Threads.push_back(tr);
	}

	int size() {
		lock_guard<recursive_mutex> locker(lock);
		return Threads.size();
	}

	xxxThread& operator[] (const int index)
	{
		lock_guard<recursive_mutex> locker(lock);
		return Threads[index];
	}
};

string outputPath = "output.txt";
string commonWords = "a  ability  able  about  above  accept  according  account  across  act  action  activity  actually  add  address  administration  admit  adult  affect  after  again  against  age  agency  agent  ago  agree  agreement  ahead  air  all  allow  almost  alone  along  already  also  although  always  American  among  amount  analysis  and  animal  another  answer  any  anyone  anything  appear  apply  approach  area  argue  arm  around  arrive  art  article  artist  as  ask  assume  at  attack  attention  attorney  audience  author  authority  available  avoid  away  baby  back  bad  bag  ball  bank  bar  base  be  beat  beautiful  because  become  bed  before  begin  behavior  behind  believe  benefit  best  better  between  beyond  big  bill  billion  bit  black  blood  blue  board  body  book  born  both  box  boy  break  bring  brother  budget  build  building  business  but  buy  by  call  camera  campaign  can  cancer  candidate  capital  car  card  care  career  carry  case  catch  cause  cell  center  central  century  certain  certainly  chair  challenge  chance  change  character  charge  check  child  choice  choose  church  citizen  city  civil  claim  class  clear  clearly  close  coach  cold  collection  college  color  come  commercial  common  community  company  compare  computer  concern  condition  conference  Congress  consider  consumer  contain  continue  control  cost  could  country  couple  course  court  cover  create  crime  cultural  culture  cup  current  customer  cut  dark  data  daughter  day  dead  deal  death  debate  decade  decide  decision  deep  defense  degree  Democrat  democratic  describe  design  despite  detail  determine  develop  development  die  difference  different  difficult  dinner  direction  director  discover  discuss  discussion  disease  do  doctor  dog  door  down  draw  dream  drive  drop  drug  during  each  early  east  easy  eat  economic  economy  edge  education  effect  effort  eight  either  election  else  employee  end  energy  enjoy  enough  enter  entire  environment  environmental  especially  establish  even  evening  event  ever  every  everybody  everyone  everything  evidence  exactly  example  executive  exist  expect  experience  expert  explain  eye  face  fact  factor  fail  fall  family  far  fast  father  fear  federal  feel  feeling  few  field  fight  figure  fill  film  final  finally  financial  find  fine  finger  finish  fire  firm  first  fish  five  floor  fly  focus  follow  food  foot  for  force  foreign  forget  form  former  forward  four  free  friend  from  front  full  fund  future  game  garden  gas  general  generation  get  girl  give  glass  go  goal  good  government  great  green  ground  group  grow  growth  guess  gun  guy  hair  half  hand  hang  happen  happy  hard  have  he  head  health  hear  heart  heat  heavy  help  her  here  herself  high  him  himself  his  history  hit  hold  home  hope  hospital  hot  hotel  hour  house  how  however  huge  human  hundred  husband  I  idea  identify  if  image  imagine  impact  important  improve  in  include  including  increase  indeed  indicate  individual  industry  information  inside  instead  institution  interest  interesting  international  interview  into  investment  involve  issue  it  item  its  itself  job  join  just  keep  key  kid  kill  kind  kitchen  know  knowledge  land  language  large  last  late  later  laugh  law  lawyer  lay  lead  leader  learn  least  leave  left  leg  legal  less  let  letter  level  lie  life  light  like  likely  line  list  listen  little  live  local  long  look  lose  loss  lot  love  low  machine  magazine  main  maintain  major  majority  make  man  manage  management  manager  many  market  marriage  material  matter  may  maybe  me  mean  measure  media  medical  meet  meeting  member  memory  mention  message  method  middle  might  military  million  mind  minute  miss  mission  model  modern  moment  money  month  more  morning  most  mother  mouth  move  movement  movie  Mr  Mrs  much  music  must  my  myself  name  nation  national  natural  nature  near  nearly  necessary  need  network  never  new  news  newspaper  next  nice  night  no  none  nor  north  not  note  nothing  notice  now  n\'t  number  occur  of  off  offer  office  officer  official  often  oh  oil  ok  old  on  once  one  only  onto  open  operation  opportunity  option  or  order  organization  other  others  our  out  outside  over  own  owner  page  pain  painting  paper  parent  part  participant  particular  particularly  partner  party  pass  past  patient  pattern  pay  peace  people  per  perform  performance  perhaps  period  person  personal  phone  physical  pick  picture  piece  place  plan  plant  play  player  PM  point  police  policy  political  politics  poor  popular  population  position  positive  possible  power  practice  prepare  present  president  pressure  pretty  prevent  price  private  probably  problem  process  produce  product  production  professional  professor  program  project  property  protect  prove  provide  public  pull  purpose  push  put  quality  question  quickly  quite  race  radio  raise  range  rate  rather  reach  read  ready  real  reality  realize  really  reason  receive  recent  recently  recognize  record  red  reduce  reflect  region  relate  relationship  religious  remain  remember  remove  report  represent  Republican  require  research  resource  respond  response  responsibility  rest  result  return  reveal  rich  right  rise  risk  road  rock  role  room  rule  run  safe  same  save  say  scene  school  science  scientist  score  sea  season  seat  second  section  security  see  seek  seem  sell  send  senior  sense  series  serious  serve  service  set  seven  several  sex  sexual  shake  share  she  shoot  short  shot  should  shoulder  show  side  sign  significant  similar  simple  simply  since  sing  single  sister  sit  site  situation  six  size  skill  skin  small  smile  so  social  society  soldier  some  somebody  someone  something  sometimes  son  song  soon  sort  sound  source  south  southern  space  speak  special  specific  speech  spend  sport  spring  staff  stage  stand  standard  star  start  state  statement  station  stay  step  still  stock  stop  store  story  strategy  street  strong  structure  student  study  stuff  style  subject  success  successful  such  suddenly  suffer  suggest  summer  support  sure  surface  system  table  take  talk  task  tax  teach  teacher  team  technology  television  tell  ten  tend  term  test  than  thank  that  the  their  them  themselves  then  theory  there  these  they  thing  think  third  this  those  though  thought  thousand  threat  three  through  throughout  throw  thus  time  to  today  together  tonight  too  top  total  tough  toward  town  trade  traditional  training  travel  treat  treatment  tree  trial  trip  trouble  true  truth  try  turn  TV  two  type  under  understand  unit  until  up  upon  us  use  usually  value  various  very  victim  view  violence  visit  voice  vote  wait  walk  wall  want  war  watch  water  way  we  weapon  wear  week  weight  well  west  western  what  whatever  when  where  whether  which  while  white  who  whole  whom  whose  why  wide  wife  will  win  wind  window  wish  with  within  without  woman  wonder  word  work  worker  world  worry  would  write  writer  wrong  yard  yeah  year  yes  yet  you  young  your  yourself";

safetyStack dataBase;
safetyStack outputBase;

safetyVector Threads;

vector<string> lineSplit(string str, bool symbolsCheck)
{
	istringstream strStream(str);
	vector<string> symbols;
	string sym;

	while (strStream >> sym)
	{
		if (symbolsCheck) {
			if (sym.length() > 1) {
				throw new exception("Found invalid character for encoding!");
			}
			else
				symbols.push_back(sym);
		}
		else
			symbols.push_back(sym);
	}

	return symbols;
}

vector<pair<string, string>> getCryptoConfig(string configFile) {

	string oldSymbols;
	string newSymbols;

	int poz = configFile.find('\n');
	oldSymbols = configFile.substr(0, poz);
	newSymbols = configFile.substr(poz + 1, configFile.length());

	vector<string> oldList = lineSplit(oldSymbols, true);
	vector<string> newList = lineSplit(newSymbols, true);

	if (oldList.size() != newList.size())
		throw exception("Characters for encoding are missing!");

	vector<pair<string, string>> cryptoConfig;
	for (int i = 0; i < oldList.size(); i++)
		cryptoConfig.push_back(make_pair(oldList[i], newList[i]));

	return cryptoConfig;
}

void encryption(int ID) {
	pair<string, string> currentPair;
	while (dataBase.pop(currentPair)) {
		//cout << "Thread# " + to_string(ID) + " get Task in db #" + to_string(dataBase.getTop() + 1) + '\n';
		Timer solveTime;
		solveTime.startTimer();

		string result = "";
		try {
			vector<pair<string, string>> cryptoConfig = getCryptoConfig(currentPair.second);

			string Line = currentPair.first;
			vector<string> lines;
			string temp = "";
			for (int i = 0; i < Line.size(); i++) {
				if (Line[i] != '\n')
					temp += Line[i];
				else
				{
					lines.push_back(temp);
					temp.clear();
				}
			}

			for (int i = 0; i < lines.size(); i++) {
				string strLine = lines[i];
				string outLine = "";

				for (int k = 0; k < strLine.length(); k++) {

					for (int j = 0; j < cryptoConfig.size(); j++)
						if (cryptoConfig[j].first[0] == strLine[k])
						{
							outLine += cryptoConfig[j].second;
							goto exit;
						}

					outLine += strLine[k];
				exit:
					continue;
				}
				result += outLine + '\n';
			}

			outputBase.push(currentPair.second, result);
			Threads[ID].taskIsSolve(solveTime.getTime());
			//cout << "Thread# " + to_string(ID) + " solve task" + '\n';
		}
		catch (const exception& el) {
			result += el.what();
			Threads[ID].taskUnsolve();
			Threads[ID].taskWithError();
			//cout << "Thread# " + to_string(ID) + " unsolve task" + '\n';
			continue;
		}
	}

	Threads[ID].setIsCloseFlag();
}

int random(const int a, const int b)
{
	static default_random_engine gen(static_cast<unsigned>(chrono::system_clock::now().time_since_epoch().count()));
	uniform_int_distribution<int> dist(a, b);
	return dist(gen);
}

void taskGenerator(int taskCount) {

	vector<string> words = lineSplit(commonWords, false);

	for (int i = 0; i < taskCount; i++) {
		vector<char> charStack;
		int iteratorCount = random(1, 199);

		string inputText = "";
		while (iteratorCount) {
			int count = random(1, 999);
			while (count) {
				inputText += words[random(1, 999)] + ' ';
				count--;
			}
			inputText += '\n';
			iteratorCount--;
		}

		string commonSymbols = "";
		for (char i = '#'; i <= '~'; ++i) {
			commonSymbols += i;
			commonSymbols += ' ';
			charStack.push_back(i);
		}

		for (int i = charStack.size() - 1; i >= 1; i--)
		{
			int j = random(0, i);
			char tmp = charStack[j];
			charStack[j] = charStack[i];
			charStack[i] = tmp;
		}
		string newSymbols = "";
		for (int i = 0; i < charStack.size(); i++) {
			newSymbols += charStack[i];
			newSymbols += ' ';
		}


		dataBase.push(inputText, commonSymbols + '\n' + newSymbols);
	}

}

void threadsGenerator(int threadCount) {

	for (int i = 0; i < threadCount; i++) {
		Threads.push_back(xxxThread(i));
		Threads[i].startThread();
	}
}

string report(double procTime) {
	string rep = "";
	string dilim = "=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=";
	string dilimT = "=^=^=^=^=^=^=^=^=^=^=^=^=^=^=^=^=^=^=^=^=^=^=^=^=^=^=^=";
	string dilimHT ="=^=^=^=^=^=^=^=^=^=^=^=^=^=";

	rep += dilimHT + "SUMMARY" + dilimHT + '\n';

	int toatlSolved = 0;
	int totalUnsolved = 0;
	int totalErrored = 0;
	double maxTime = Threads[0].getMaxSolveTime();
	double minTime = Threads[0].getMaxSolveTime();

	for (int i = 0; i < Threads.size(); i++)
	{
		toatlSolved += Threads[i].getSolveTasks();
		totalUnsolved += Threads[i].getUnsolveTasks();
		totalErrored += Threads[i].getErrorTasks();

		if (Threads[i].getMaxSolveTime() > maxTime)
			maxTime = Threads[i].getMaxSolveTime();

		if (Threads[i].getMinSolveTime() < minTime && Threads[i].getMinSolveTime() != 0)
			minTime = Threads[i].getMinSolveTime();
	}

	rep += "Total programm time:\t" + to_string(procTime) + " (s)" + '\n'
		+ "Total solved problems:\t" + to_string(toatlSolved) + '\n'
		+ "Total unsolved problems:\t" + to_string(totalUnsolved) + '\n'
		+ "Total problems with errors:\t" + to_string(totalErrored) + '\n'
		+ "Maximum solve time:\t" + to_string(maxTime) + " (s)" + '\n'
		+ "Minimum solve time:\t" + to_string(minTime) + " (s)" + '\n' + dilim + "\n\n";

	for (int i = 0; i < Threads.size(); i++) {
		rep += dilimHT + "THREAD(" + to_string(Threads[i].getThreadID()) + ')' + dilimHT + '\n'
			+ "Total solved problems:\t" + to_string(Threads[i].getSolveTasks()) + '\n'
			+ "Total unsolved problems:\t" + to_string(Threads[i].getUnsolveTasks()) + '\n'
			+ "Total solve time:\t" + to_string(Threads[i].getWorkTime()) + " (s)" + '\n'
			+ "Maximum solve time:\t" + to_string(Threads[i].getMaxSolveTime()) + " (s)" + '\n'
			+ "Minimum solve time:\t" + to_string(Threads[i].getMinSolveTime()) + " (s)" + "\n\n";
	}

	rep += dilim + '\n';
	return rep;
}

int main() {

	Timer one;
	int taskCount = 0;
	int threadCount = 0;

	cout << "Task count:\n";
	cin >> taskCount;
	cout << "Thread count:\n";
	cin >> threadCount;

	if (taskCount <= 0 || threadCount <= 0) {
		cout << "Wrong data entered!" << endl;
		return 0;
	}

	one.startTimer();
	taskGenerator(taskCount);
	threadsGenerator(threadCount);

	bool aim = true;

	while (aim) {
		for (int i = 0; i < Threads.size(); i++) {
			if (Threads[i].getAlive())
				break;
			if (i == Threads.size() - 1)
				aim = false;
		}
		Sleep(1);
	}

	cout << report(one.getTime());

	one.resetTimer();
	ofstream out(outputPath);
	pair<string, string> currentPair;
	while (outputBase.pop(currentPair)) {
		out << "CONFIGURE DATA\n##################################\n\n" + currentPair.first + '\n'
			<< "OUTPUT DATA\n##################################\n\n" + currentPair.second + '\n';
	}
	cout << "Writefile time: " << one.getTime() << " (s)" << endl;

	return 0;
}



