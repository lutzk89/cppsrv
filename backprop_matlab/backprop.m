nin = 20;
nhi = 5;
nou = 10;

eta = 3.0; %learning rate

x=rand(20,10);
y=rand(10,10);
%load data

%[fna rem] = strtok(files); % octave version
nh = 10;

%while numel(fna) > 10

nsam = size(x,2);
ntarg = size(y,1);

%fully connected
nge = nhi + 2; % hidden + input + output
w = rand(nin,nin,nge);
b = rand(nin,nge);

f = @(x) 1 ./ ( 1 + exp( - x ) );
fprime = @(x) exp( -x ) ./ ( ( 1 + exp( - x ) ).^2 );
s = 10^(-9);
delta = 2 * s;
dlog =  [];
flog = [];
iteration=1;
fprev = 0;
while delta > s
    derr = zeros(nin,nge,size(x,2));
    act = zeros(nin,nge,size(x,2));
    zvec = zeros(nin,nge,size(x,2));
    delta = 0;
    fval = 0;
    for k = 1:nsam
        act(:,1,k) = x(:,k);
        for i = 2:nge
            zvec(:,i,k) = w(:,:,i) * act(:,i-1,k) + b(:,i);
            act(:,i,k) = f( zvec(:,i,k) );
        end
	    fval = delta + sum ( ( act(1:ntarg,nge,k) - y(1:ntarg,k) ).^2);
        derr(1:ntarg,nge,k) = ( act(1:ntarg,nge,k) - y(:,k) ) .* fprime( zvec(1:ntarg,nge,k) );
        for m=(nge-1):(-1):1
            derr(:,m,k) = ( transpose( w(:,:,m+1) ) * derr(:,m+1,k) ) .* fprime( zvec(:,m,k) );
        end
    end
    % update weights
    delta = sum( sum( sum( abs( derr ) ) ) );
    %eta = max(0.01, min(100, 1000*(fval - fprev)));
    if ( fprev > 0 )
        if ( fval == fprev )
            eta = 0.01;
        else
            eta = 3.0;
        end
    end
    fprev = fval;
    dlog = [ dlog; delta ];
    %flog = [ flog ; fval ];
    disp(['Error ' num2str(fval) ' in Iteration ' num2str(iteration) ' Stop Level ' num2str(100*delta/s) '% eta ' num2str(eta)]);
    plot(dlog)
    %figure(2), plot(flog);
    drawnow
    iteration = iteration + 1;
    dw = zeros(size(w));
    db = zeros(size(b));
    for k=2:nge
        for xn = 1 : nsam
            dw(:,:,k) = dw(:,:,k) + ( eta / (numel(w(:,:,k))) ) * derr(:,k,xn) * transpose( act(:,k-1,xn) );
            db(:,k) = db(:,k) + ( eta / (numel(w(:,:,k))) ) * derr(:,k,xn);
        end
    end
    w = w - dw;
    b = b - db;
end
